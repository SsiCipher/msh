/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:27:07 by yanab             #+#    #+#             */
/*   Updated: 2022/08/28 23:22:48 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_node	*create_node(t_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->type = type;
	node->argv = NULL;
	node->argc = 0;
	node->input_fd = STDIN_FILENO;
	node->output_fd = STDOUT_FILENO;
	node->exit_code = EXIT_SUCCESS;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	free_tree(t_node *root)
{
	int	i;

	if (!root)
		return ;
	free_tree(root->right);
	free_tree(root->left);
	i = -1;
	while (root->argv != NULL && root->argv[++i])
		free(root->argv[i]);
	if (root->input_fd != STDIN_FILENO)
		close(root->input_fd);
	if (root->output_fd != STDOUT_FILENO)
		close(root->output_fd);
	free(root->argv);
	free(root);
}

void	node_argv_push(t_node *node, char *new_arg)
{
	node->argv = realloc(node->argv, sizeof(char *) * (node->argc + 2));
	node->argv[node->argc] = strdup(new_arg);
	node->argv[node->argc + 1] = NULL;
	node->argc += 1;
}

void	update_io_fds(t_node *node, t_type type, char *filename)
{
	if (
		(type == R_INPUT || type == R_HEREDOC)
		&& node->input_fd != STDIN_FILENO
	)
		close(node->input_fd);
	if (
		(type == R_OUTPUT || type == R_APPEND)
		&& node->output_fd != STDOUT_FILENO
	)
		close(node->output_fd);
	if (type == R_INPUT || type == R_HEREDOC)
		node->input_fd = open(filename, O_RDONLY, 0666);
	if (type == R_OUTPUT)
		node->output_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (type == R_APPEND)
		node->output_fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
}
