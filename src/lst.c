/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:18:16 by yanab             #+#    #+#             */
/*   Updated: 2022/07/22 17:49:44 by cipher           ###   ########.fr       */
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
	t_token	*end_list;

	if (!tokens_lst)
		return ;
	if (*tokens_lst == NULL)
		*tokens_lst = new_token;
	else
	{
		end_list = *tokens_lst;
		while (end_list->next)
			end_list = end_list->next;
		new_token->prev = end_list;
		end_list->next = new_token;
	}
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
 * Get the last token in the list of tokens
 * 
 * @param	tokens_lst the list of tokens
 * @return	t_token struct that holds the last token
 */
t_token	*last_token(t_token *tokens_lst)
{
	t_token	*tk;

	if (!tokens_lst)
		return (NULL);
	tk = tokens_lst;
	while (tk->next)
		tk = tk->next;
	return (tk);
}

/**
 * Free the memory allocated for the tokens list and set it to NULL
 * 
 * @param	tokens_lst the list to free
 */
void	free_tokens(t_token **tokens_lst)
{
	t_token	*curr;

	curr = *tokens_lst;
	while (curr)
	{
		free(curr->content);
		free(curr);
		curr = curr->next;
	}
	*tokens_lst = NULL;
}