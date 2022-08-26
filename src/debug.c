/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:36:12 by cipher            #+#    #+#             */
/*   Updated: 2022/08/26 18:41:52 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*get_type_name(t_type type)
{
	if (type == S_QUOTE)
		return ("S_QUOTE");
	else if (type == D_QUOTE)
		return ("D_QUOTE");
	else if (type == R_HEREDOC)
		return ("R_HEREDOC");
	else if (type == R_APPEND)
		return ("R_APPEND");
	else if (type == R_INPUT)
		return ("R_IN");
	else if (type == R_OUTPUT)
		return ("R_OUT");
	else if (type == O_PARENTH)
		return ("O_PARENTH");
	else if (type == C_PARENTH)
		return ("C_PARENTH");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else if (type == PIPE)
		return ("PIPE");
	else
		return ("CMD");
}

void	print_tokens(t_token *tokens_lst)
{
	t_token	*curr_tk;

	curr_tk = tokens_lst;
	while (curr_tk)
	{
		printf("%s[%d]\t=\t[%s]\n",
			get_type_name(curr_tk->type),
			curr_tk->length,
			curr_tk->content);
		curr_tk = curr_tk->next;
	}
}

void	print_node(t_node *node)
{
	int	i;

	printf("%d,%d -> ", node->input_fd, node->output_fd);
	if (node->type != CMD)
		printf("%s", get_type_name(node->type));
	else
	{
		i = -1;
		while (++i < node->argc)
		{
			if (i != 0)
				printf(" ");
			printf("[%s]", node->argv[i]);
		}
	}
	printf("\n");
}

void	print_tree(t_node *root, int level)
{
	int	i;

	if (!root)
		return ;
	print_tree(root->right, level + 1);
	i = -1;
	while (++i < level * 16)
		printf(" ");
	print_node(root);
	print_tree(root->left, level + 1);
}
