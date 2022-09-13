/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/09/13 20:54:07 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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

void	exec_pipe(t_node *node, t_env *env)
{
	int pipe_ends[2];
	int	pid_left;
	int cmd_exec;

	if (pipe(pipe_ends) == -1)
		return ;
	pid_left = fork();
	if (pid_left == 0)
	{
		dup_pipe(pipe_ends, STDOUT_FILENO);
		if (!ft_strchr(node->argv[0], '/'))
			cmd_exec = execve(get_cmd_path(node->argv[0], env),
					node->argv, env->content);
		else
			cmd_exec = execve(node->argv[0], node->argv, env->content);
		if (cmd_exec == -1)
			print_err("msh: Command not found: ", node->argv[0]);
	}
	close(pipe_ends[STDIN_FILENO]);
	close(pipe_ends[STDOUT_FILENO]);
	waitpid(pid_left, NULL, 0);
}

int	exec_ast(t_node *node, t_env *env)
{
	if (node->type == CMD)
		return (exec_cmd(node, env));
	else if (node->type == PIPE)
	{
		exec_ast(node->left, env);		
		exec_ast(node->right, env);
	}
	return (EXIT_SUCCESS);
}
