/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:27:07 by yanab             #+#    #+#             */
/*   Updated: 2022/08/22 05:33:57 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_ast_node	*create_node(t_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
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

void	node_argv_push(t_ast_node *node, char *new_arg)
{
	node->argv = realloc(node->argv, sizeof(char *) * (node->argc + 2));
	node->argv[node->argc] = strdup(new_arg);
	node->argv[node->argc + 1] = NULL;
	node->argc += 1;
}

// (void)node;
// (void)type;
// (void)filename;
void	update_io_fds(t_ast_node *node, t_type type, char *filename)
{
	if (type == R_INPUT && node->input_fd != STDIN_FILENO)
		close(node->input_fd);
	if ((type == R_OUTPUT || type == R_APPEND) && node->output_fd != 1)
		close(node->output_fd);
	if (type == R_INPUT)
		node->input_fd = open(filename, O_RDONLY, 0666);
	if (type == R_OUTPUT)
		node->output_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (type == R_APPEND)
		node->output_fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
}

// TODO: handle heredoc redirection in tree

t_ast_node	*create_ast(t_token *tkns_lst)
{
	t_ast_node	*ast_root;
	t_ast_node	*curr_node;
	t_token		*curr_tkn;
	bool		inside_parenth;

	ast_root = NULL;
	curr_node = NULL;
	curr_tkn = tkns_lst;
	inside_parenth = false;
	while (curr_tkn)
	{
		if (curr_tkn->type == CMD)
		{
			if (!ast_root)
			{
				curr_node = create_node(CMD);
				ast_root = curr_node;
			}
			else if (curr_node->type != CMD)
			{
				curr_node = create_node(CMD);
				if (!ast_root->right)
					ast_root->right = curr_node;
				else
					ast_root->right->right = curr_node;
			}
			node_argv_push(curr_node, curr_tkn->content);
		}
		else if (curr_tkn->type == PIPE || curr_tkn->type == AND
			|| curr_tkn->type == OR)
		{
			curr_node = create_node(curr_tkn->type);
			if ((curr_tkn->type == PIPE && ast_root->type != CMD
					&& ast_root->type != PIPE) || inside_parenth)
			{
				if (ast_root->right && inside_parenth)
				{
					curr_node->left = ast_root->right;
					ast_root->right = curr_node;
				}
				else
				{
					curr_node->left = ast_root;
					ast_root = curr_node;
				}
			}
			else
			{
				curr_node->left = ast_root;
				ast_root = curr_node;
			}
		}
		else if (curr_tkn->type == R_INPUT || curr_tkn->type == R_OUTPUT
			|| curr_tkn->type == R_APPEND)
		{
			if (!ast_root)
			{
				curr_node = create_node(CMD);
				ast_root = curr_node;
			}
			else if (curr_node->type != CMD)
			{
				curr_node = create_node(CMD);
				if (!ast_root->right)
					ast_root->right = curr_node;
				else
					ast_root->right->right = curr_node;
			}
			update_io_fds(curr_node, curr_tkn->type, curr_tkn->next->content);
			curr_tkn = curr_tkn->next;
		}
		else if (curr_tkn->type == O_PARENTH || curr_tkn->type == C_PARENTH)
		{
			if (curr_tkn->type == O_PARENTH)
				inside_parenth = true;
			else
				inside_parenth = false;
		}
		curr_tkn = curr_tkn->next;
	}
	return (ast_root);
}
