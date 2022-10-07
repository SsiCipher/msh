/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:55:56 by yanab             #+#    #+#             */
/*   Updated: 2022/10/04 22:28:47 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	print_err(char *error_msg, char *arg)
{
	if (arg)
		error_msg = ft_strjoin(error_msg, arg);
	ft_putstr_fd(error_msg, 2);
	write(2, "\n", 1);
	exit(127);
}

void	dup_io(t_node *node, int tmp_io[2])
{
	if (node->input_fd != STDIN_FILENO)
	{
		tmp_io[STDIN_FILENO] = dup(STDIN_FILENO);
		dup2(node->input_fd, STDIN_FILENO);
	}
	if (node->output_fd != STDOUT_FILENO)
	{
		tmp_io[STDOUT_FILENO] = dup(STDOUT_FILENO);
		dup2(node->output_fd, STDOUT_FILENO);
	}
}

void	dup_pipe(int pipe_ends[2], int std_fd)
{
	if (std_fd == STDIN_FILENO)
	{
		dup2(pipe_ends[STDIN_FILENO], STDIN_FILENO);
		close(pipe_ends[STDIN_FILENO]);
		close(pipe_ends[STDOUT_FILENO]);
	}
	else if (std_fd == STDOUT_FILENO)
	{
		dup2(pipe_ends[STDOUT_FILENO], STDOUT_FILENO);
		close(pipe_ends[STDIN_FILENO]);
		close(pipe_ends[STDOUT_FILENO]);
	}
}

void	close_io(t_node *node, int tmp_io[2])
{
	if (node->input_fd != STDIN_FILENO)
	{
		dup2(tmp_io[STDIN_FILENO], STDIN_FILENO);
		close(tmp_io[STDIN_FILENO]);
		close(node->input_fd);
	}
	if (node->output_fd != STDOUT_FILENO)
	{
		dup2(tmp_io[STDOUT_FILENO], STDOUT_FILENO);
		close(tmp_io[STDOUT_FILENO]);
		close(node->output_fd);
	}
}
