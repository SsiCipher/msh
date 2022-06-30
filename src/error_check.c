/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:56:26 by yanab             #+#    #+#             */
/*   Updated: 2022/06/30 10:08:12 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Check tokens for syntax errors
 * 
 * @param	expected the expected token after
 * @param	tkn_content the content of the token
 * @return	true always
 */
bool	syntax_error(char *expected, char *tkn_content)
{
	printf(
		"msh: syntax error: expected a %s after %s\n",
		expected,
		tkn_content);
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
		if (
			(tk->type == REDIRECT_IN || tk->type == REDIRECT_OUT
				|| tk->type == REDIRECT_APPEND)
			&& (tk->next == NULL || tk->next->type != SIMPLE_CMD)
		)
			return (syntax_error("file", tk->content));
		else if (
			(tk->type == PIPE || tk->type == AND || tk->type == OR)
			&& (tk->next == NULL || tk->next->type != SIMPLE_CMD)
		)
			return (syntax_error("command", tk->content));
		else if (
			tk->type == DOUBLE_QUOTE && ft_countchr(tk->content, '"') != 2
		)
			return (printf("msh: unclosed quotes: enter a matching \"\n"));
		else if (
			tk->type == SINGLE_QUOTE && ft_countchr(tk->content, '\'') != 2
		)
			return (printf("msh: unclosed quotes: enter a matching '\n"));
		tk = tk->next;
	}
	return (false);
}
