/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/10/12 22:17:20 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

// TODO: [x] Edit builtins to return exit_codes
// TODO: [x] Set exit_code to global variable
// TODO: [ ] change heredoc to pipe
// TODO: [x] close unused fds
// TODO: [ ] dont skip : in path split (in case a directory is named ":blabla")

int	exec_single_cmd(t_node *node, t_env *env)
{
	int	exit_code;

	if (
		is_builtin(node->argv[0])
		&& !ft_strchr(node->argv[0], '/')
	)
		exit_code = run_builtin(node, env);
	else
		exit_code = run_cmd(node, env);
	node->exit_code = exit_code;
	return (exit_code);
}

int	g_tmp_in = -1;

int	exec_pipe(t_node *node, t_env *env, int pipe_ends[2], bool is_last)
{
	int	pid;
	int	tmp_io[2];

	pid = fork();
	if (pid == -1)
		perror("msh: fork: ");
	else if (pid == 0)
	{
		if (!is_last)
			dup_pipe(pipe_ends, STDOUT_FILENO);
		if (
			is_builtin(node->argv[0])
			&& !ft_strchr(node->argv[0], '/')
		)
			exit(run_builtin(node, env));
		else
			_run_cmd(node, env, tmp_io);
	}
	else
	{
		if (g_tmp_in == -1)
			g_tmp_in = dup(STDIN_FILENO);
		if (!is_last)
		{
			dup_pipe(pipe_ends, STDIN_FILENO);
			pipe(pipe_ends);
		}
		else
		{
			close(pipe_ends[STDIN_FILENO]);
			close(pipe_ends[STDOUT_FILENO]);
			dup2(g_tmp_in, STDIN_FILENO);
			close(g_tmp_in);
			g_tmp_in = -1;
		}
	}
	return (pid);
}

void	exec_pipe_rec(t_node *node, t_env *env, int *pipe_ends)
{
	if (node->type == CMD)
		exec_pipe(node, env, pipe_ends, false);
	else if (node->type == PIPE)
	{
		exec_pipe_rec(node->left, env, pipe_ends);
		exec_pipe(node->right, env, pipe_ends, false);
	}
}

int	exec_ast(t_node *node, t_env *env)
{
	int		pipe_ends[2];
	int		status;
	pid_t	last_pid;
	pid_t	pid;

	if (node->type == CMD)
		return (exec_single_cmd(node, env));
	else if (node->type == PIPE)
	{
		pipe(pipe_ends);
		exec_pipe_rec(node->left, env, pipe_ends);
		last_pid = exec_pipe(node->right, env, pipe_ends, true);
		close(pipe_ends[STDIN_FILENO]);
		close(pipe_ends[STDOUT_FILENO]);
		while ((pid = waitpid(-1, &status, 0)) != -1)
		{	
			if (WIFEXITED(status) && pid == last_pid)
				return (WEXITSTATUS(status));
		}
	}
	return (EXIT_SUCCESS);
}
