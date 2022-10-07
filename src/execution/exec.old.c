/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/10/04 22:29:15 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

// TODO: [x] Edit builtins to return exit_codes
// TODO: [x] Set exit_code to global variable
// TODO: [ ] change heredoc to pipe
// TODO: [x] close unused fds
// TODO: [ ] dont skip : in path split (in case a directory is named ":blabla")

int	exec_cmd(t_node *node, t_env *env)
{
	int	exit_code;

	if (is_builtin(node->argv[0]) && !ft_strchr(node->argv[0], '/'))
		exit_code = run_builtin(node, env);
	else
		exit_code = run_cmd(node, env);
	node->exit_code = exit_code;
	return (exit_code);
}

int	exec_pipe(t_node *node, t_env *env)
{
	int pipe_ends[2];

	if (pipe(pipe_ends) == -1)
		return (EXIT_FAILURE);

	int pid_left = fork();
	if (pid_left == 0)
	{
		close(pipe_ends[STDIN_FILENO]);
		dup2(pipe_ends[STDOUT_FILENO], STDOUT_FILENO);
		close(pipe_ends[STDOUT_FILENO]);
		int cmd_exec = execve(node->left->argv[0], node->left->argv, env->content);
		if (cmd_exec == -1)
			print_err("msh: Command not found: ", node->left->argv[0]);
	}
	int pid_right = fork();
	if (pid_right == 0)
	{
		close(pipe_ends[STDOUT_FILENO]);
		dup2(pipe_ends[STDIN_FILENO], STDIN_FILENO);
		close(pipe_ends[STDIN_FILENO]);
		int cmd_exec = execve(node->right->argv[0], node->right->argv, env->content);
		if (cmd_exec == -1)
			print_err("msh: Command not found: ", node->right->argv[0]);
	}
	close(pipe_ends[STDIN_FILENO]);
	close(pipe_ends[STDOUT_FILENO]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
	return (0);
}

int	exec_ast(t_node *node, t_env *env)
{
	if (node->type == PIPE)
		return (exec_pipe(node, env));
	else if (node->type == CMD)
		return (exec_cmd(node, env));
	return (EXIT_SUCCESS);
}
