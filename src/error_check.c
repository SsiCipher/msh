/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:56:26 by yanab             #+#    #+#             */
/*   Updated: 2022/08/25 05:36:33 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

// TODO: fix norm errors

/**
 * Check tokens for syntax errors
 * 
 * @param	token_lst the list of tokens
 * @return	true if any errors were found false otherwise
 */
bool	check_errors(t_token *tkn)
{
	bool	is_inside_parenth;

	is_inside_parenth = false;
	while (tkn)
	{
		if (is_next_invalid(tkn, R_HEREDOC, CMD))
			return (display_error("unexpected token", "newline"));
		else if (
			is_next_invalid(tkn, R_INPUT, CMD)
			|| is_next_invalid(tkn, R_OUTPUT, CMD)
			|| is_next_invalid(tkn, R_APPEND, CMD)
		)
			return (display_error("unexpected token", "newline"));
		else if (
			(is_both_invalid(tkn, OR, CMD)
				&& is_next_invalid(tkn, OR, O_PARENTH)
				&& is_prev_invalid(tkn, OR, C_PARENTH))
			|| (is_both_invalid(tkn, AND, CMD)
				&& is_next_invalid(tkn, AND, O_PARENTH)
				&& is_prev_invalid(tkn, AND, C_PARENTH))
		)
			return (display_error("unexpected token", tkn->content));
		else if (
			is_both_invalid(tkn, PIPE, CMD)
			&& is_next_invalid(tkn, PIPE, R_HEREDOC)
			&& is_prev_invalid(tkn, PIPE, C_PARENTH)
			&& is_next_invalid(tkn, PIPE, R_INPUT)
			&& is_next_invalid(tkn, PIPE, R_OUTPUT)
			&& is_next_invalid(tkn, PIPE, R_APPEND)
		)
			return (display_error("unexpected token", tkn->content));
		else if (tkn->type == CMD && is_quotes_unclosed(tkn->content))
			return (display_error("unexpected end of file", NULL));
		else if (tkn->type == O_PARENTH)
		{
			if (
				is_next_invalid(tkn, O_PARENTH, CMD)
				&& is_next_invalid(tkn, PIPE, R_INPUT)
				&& is_next_invalid(tkn, PIPE, R_OUTPUT)
				&& is_next_invalid(tkn, PIPE, R_APPEND)
			)
				return (display_error("unexpected end of file", NULL));
			else
				is_inside_parenth = true;
		}
		else if (tkn->type == C_PARENTH)
		{
			if (is_inside_parenth)
				is_inside_parenth = false;
			else
				return (display_error("unexpected token", ")"));
		}
		tkn = tkn->next;
	}
	if (is_inside_parenth)
		return (display_error("unexpected end of file", NULL));
	return (false);
}
