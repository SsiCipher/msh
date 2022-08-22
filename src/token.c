/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:18:16 by yanab             #+#    #+#             */
/*   Updated: 2022/08/22 10:15:27 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Create a new token
 * 
 * @param	content the content of the token
 * @param	type the type of the token from the t_type enum
 * @param	length the length of the token
 * @return	t_token struct that holds the new token
 */
t_token	*create_token(char *content, t_type type, int length)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->content = ft_substr(content, 0, length);
	new_token->type = type;
	new_token->length = length;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

/**
 * Add a token to a list
 * 
 * @param	tokens_lst the list to add the token to
 * @param	new_token the new token to add
 */
void	push_token(t_token **tokens_lst, t_token *new_token)
{
	t_token	*list_tail;

	if (!tokens_lst)
		return ;
	if (*tokens_lst == NULL)
		*tokens_lst = new_token;
	else
	{
		list_tail = *tokens_lst;
		while (list_tail->next)
			list_tail = list_tail->next;
		new_token->prev = list_tail;
		list_tail->next = new_token;
	}
}

void	insert_token(t_token *target_token, t_token *new_token)
{
	// new_token->prev = target_token;
	new_token->next = target_token;
	// target_token->next->prev = new_token;
	target_token->next = new_token;
}

/**
 * Delete a token from the list and free its content
 * 
 * @param	token the token to delete
 */
void	delete_token(t_token *token)
{
	if (!token)
		return ;
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free(token->content);
	free(token);
}

/**
 * Free the memory allocated for the tokens list and set it to NULL
 * 
 * @param	tokens_lst the list to free
 */
void	free_tokens(t_token **tokens_lst)
{
	t_token	*curr;
	t_token	*tmp;

	curr = *tokens_lst;
	while (curr)
	{
		free(curr->content);
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*tokens_lst = NULL;
}
