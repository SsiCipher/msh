/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:27:07 by yanab             #+#    #+#             */
/*   Updated: 2022/08/28 15:00:51 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	handle_cmd(t_token *tkn, t_node **root, t_node **node)
{
	if (!(*root))
	{
		*node = create_node(CMD);
		*root = *node;
	}
	else if ((*node)->type != CMD)
	{
		*node = create_node(CMD);
		if (!(*root)->right)
			(*root)->right = *node;
		else
			(*root)->right->right = *node;
	}
	node_argv_push(*node, tkn->content);
}

void	handle_pipe(t_node **root, t_node **node)
{
	*node = create_node(PIPE);
	if ((*root)->type == AND || (*root)->type == OR)
	{
		(*node)->left = (*root)->right;
		(*root)->right = *node;
	}
	else
	{
		(*node)->left = *root;
		*root = *node;
	}
}

void	handle_logical_op(t_token *tkn, t_node **root, t_node **node,
	bool is_inside_parenth)
{
	*node = create_node(tkn->type);
	if (is_inside_parenth)
	{
		(*node)->left = (*root)->right;
		(*root)->right = *node;
	}
	else
	{
		(*node)->left = *root;
		*root = *node;
	}
}

void	handle_redirections(t_token **tkn, t_node **root, t_node **node)
{
	if (!(*root))
	{
		*node = create_node(CMD);
		*root = *node;
	}
	else if ((*node)->type != CMD)
	{
		*node = create_node(CMD);
		if (!(*root)->right)
			(*root)->right = *node;
		else
			(*root)->right->right = *node;
	}
	update_io_fds(*node, (*tkn)->type, (*tkn)->next->content);
	*tkn = (*tkn)->next;
}

t_node	*create_ast(t_token *tkns_lst)
{
	t_node		*ast_root;
	t_node		*curr_node;
	t_token		*curr_tkn;
	bool		inside_parenth;

	ast_root = NULL;
	curr_node = NULL;
	curr_tkn = tkns_lst;
	inside_parenth = false;
	while (curr_tkn)
	{
		if (curr_tkn->type == CMD)
			handle_cmd(curr_tkn, &ast_root, &curr_node);
		else if (curr_tkn->type == PIPE)
			handle_pipe(&ast_root, &curr_node);
		else if (curr_tkn->type == AND || curr_tkn->type == OR)
			handle_logical_op(curr_tkn, &ast_root, &curr_node, inside_parenth);
		else if (curr_tkn->type == R_INPUT || curr_tkn->type == R_OUTPUT
			|| curr_tkn->type == R_APPEND || curr_tkn->type == R_HEREDOC)
			handle_redirections(&curr_tkn, &ast_root, &curr_node);
		else if (curr_tkn->type == O_PARENTH || curr_tkn->type == C_PARENTH)
			inside_parenth = curr_tkn->type == O_PARENTH;
		curr_tkn = curr_tkn->next;
	}
	return (ast_root);
}
