/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/10/13 23:30:15 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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

int	exec_pipe_r(t_node *node, t_env *env, int *pipe_ends, bool is_last)
{
	if (node->type == CMD)
		exec_pipe(node, env, pipe_ends, is_last);
	else if (node->type == PIPE)
	{
		exec_pipe_r(node->left, env, pipe_ends, false);
		return (exec_pipe(node->right, env, pipe_ends, is_last));
	}
	return (EXIT_SUCCESS);
}

int	exec_ast(t_node *node, t_env *env)
{
	int		pipe_ends[2];
	int		status;
	pid_t	last_pid;
	pid_t	pid;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	if (node->type == CMD)
		return (exec_single_cmd(node, env));
	else if (node->type == PIPE)
	{
		pipe(pipe_ends);
		last_pid = exec_pipe_r(node, env, pipe_ends, true);
		close(pipe_ends[STDIN_FILENO]);
		close(pipe_ends[STDOUT_FILENO]);
		while ((pid = waitpid(-1, &status, 0)) != -1)
		{	
			if (WIFEXITED(status) && pid == last_pid)
				exit_code = WEXITSTATUS(status);
		}
	}
	else if (node->type == AND || node->type == OR)
	{
		exit_code = exec_ast(node->left, env);
		if (
			(node->type == AND && exit_code == 0)
			|| (node->type == OR && exit_code != 0)
		)
			return (exec_ast(node->right, env));
	}
	return (exit_code);
}
