/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:56:26 by yanab             #+#    #+#             */
/*   Updated: 2022/08/10 02:53:31 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Check tokens for syntax errors
 * 
 * @param	expected the expected token after
 * @param	tkn_content the content of the token
 * @return	always true
 */
bool	print_error(char *error_type, char *expected, char *tkn_content)
{
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd(error_type, 2);
	ft_putstr_fd(" error: ", 2);
	if (expected)
	{
		ft_putstr_fd("expected a ", 2);
		ft_putstr_fd(expected, 2);
	}
	if (tkn_content)
	{
		ft_putstr_fd(" after ", 2);
		ft_putstr_fd(tkn_content, 2);
	}
	ft_putchar_fd('\n', 2);
	return (true);
}

/**
 * Check tokens for syntax errors
 * 
 * @param	token_lst the list of tokens
 * @return	true if any errors were found false otherwise
 */
bool	check_errors(t_token *token_lst)
{
	t_token	*tk;

	tk = token_lst;
	while (tk)
	{
		if (tk->type == HERE_DOC && (!(tk->next) || tk->next->type != CMD))
			return (print_error("syntax", "limiter", tk->content));
		else if (
			(tk->type == REDIRECT_IN || tk->type == REDIRECT_OUT
				|| tk->type == REDIRECT_APPEND)
			&& (!(tk->next) || tk->next->type != CMD)
		)
			return (print_error("syntax", "file", tk->content));
		else if (
			(tk->type == AND || tk->type == OR)
			&& (!(tk->next) || (tk->next->type != CMD && tk->next->type != OPEN_PARENTH))
		)
			return (print_error("syntax", "command", tk->content));
		else if (
			tk->type == PIPE
			&& (
				!(tk->next)
				&& (tk->next->type != REDIRECT_IN
				|| tk->next->type != REDIRECT_OUT
				|| tk->next->type != REDIRECT_APPEND
				|| tk->next->type != HERE_DOC
				|| tk->next->type != CMD)
			)
		)
			return (print_error("syntax", "commandd", tk->content));
		else if (
			tk->type == CMD && ft_countchr(tk->content, '"') % 2 != 0
		)
			return (print_error("syntax", "matching `\"` quote", NULL));
		else if (
			tk->type == CMD && ft_countchr(tk->content, '\'') % 2 != 0
		)
			return (print_error("syntax", "matching `\'` quote", NULL));
		tk = tk->next;
	}
	return (false);
}
