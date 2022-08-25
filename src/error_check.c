/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:56:26 by yanab             #+#    #+#             */
/*   Updated: 2022/08/25 15:10:23 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Check a token for redirection syntax errors
 * 
 * @param	tkn the token to check
 * @return	true if any errors were found false otherwise
 */
bool	check_redirection(t_token *tkn)
{
	if (!is_next_valid(tkn, R_HEREDOC, CMD))
		return (display_error("unexpected token", "newline"));
	else if (
		!is_next_valid(tkn, R_INPUT, CMD)
		|| !is_next_valid(tkn, R_OUTPUT, CMD)
		|| !is_next_valid(tkn, R_APPEND, CMD)
	)
		return (display_error("unexpected token", "newline"));
	return (false);
}

/**
 * Check a token for logical_and_or syntax errors
 * 
 * @param	tkn the token to check
 * @return	true if any errors were found false otherwise
 */
bool	check_logical_and_or(t_token *tkn)
{
	if (
		(
			!is_both_valid(tkn, OR, CMD)
			&& !is_next_valid(tkn, OR, O_PARENTH)
			&& !is_prev_valid(tkn, OR, C_PARENTH)
			&& !is_next_valid(tkn, OR, R_INPUT)
			&& !is_next_valid(tkn, OR, R_OUTPUT)
			&& !is_next_valid(tkn, OR, R_APPEND)
		)
		|| (
			!is_both_valid(tkn, AND, CMD)
			&& !is_next_valid(tkn, AND, O_PARENTH)
			&& !is_prev_valid(tkn, AND, C_PARENTH)
			&& !is_next_valid(tkn, AND, R_INPUT)
			&& !is_next_valid(tkn, AND, R_OUTPUT)
			&& !is_next_valid(tkn, AND, R_APPEND)
		)
	)
		return (display_error("unexpected token", tkn->content));
	return (false);
}

/**
 * Check a token for pipe syntax errors
 * 
 * @param	tkn the token to check
 * @return	true if any errors were found false otherwise
 */
bool	check_pipe(t_token *tkn)
{
	if (
		!is_both_valid(tkn, PIPE, CMD)
		&& !is_prev_valid(tkn, PIPE, C_PARENTH)
		&& !is_next_valid(tkn, PIPE, R_HEREDOC)
		&& !is_next_valid(tkn, PIPE, R_INPUT)
		&& !is_next_valid(tkn, PIPE, R_OUTPUT)
		&& !is_next_valid(tkn, PIPE, R_APPEND)
	)
		return (display_error("unexpected token", tkn->content));
	return (false);
}

/**
 * Check a token for parenthesis syntax errors
 * 
 * @param	tkn the token to check
 * @return	true if any errors were found false otherwise
 */
bool	check_parenthesis(t_token *tkn, bool *is_inside_parenth)
{
	if (tkn->type == O_PARENTH)
	{
		if (
			!is_next_valid(tkn, O_PARENTH, CMD)
			&& !is_next_valid(tkn, O_PARENTH, R_INPUT)
			&& !is_next_valid(tkn, O_PARENTH, R_OUTPUT)
			&& !is_next_valid(tkn, O_PARENTH, R_APPEND)
		)
			return (display_error("unexpected end of file", NULL));
		else
			*is_inside_parenth = true;
	}
	else if (tkn->type == C_PARENTH)
	{
		if (*is_inside_parenth)
			*is_inside_parenth = false;
		else
			return (display_error("unexpected token", ")"));
	}
	return (false);
}

/**
 * Check tokens for syntax errors
 * 
 * @param	tkn the list of tokens
 * @return	true if any errors were found false otherwise
 */
bool	check_errors(t_token *tkn)
{
	bool	is_inside_parenth;

	is_inside_parenth = false;
	while (tkn)
	{
		if (
			check_redirection(tkn)
			|| check_logical_and_or(tkn)
			|| check_pipe(tkn)
			|| check_parenthesis(tkn, &is_inside_parenth)
		)
			return (true);
		else if (tkn->type == CMD && is_quotes_unclosed(tkn->content))
			return (display_error("unexpected end of file", NULL));
		tkn = tkn->next;
	}
	if (is_inside_parenth)
		return (display_error("unexpected end of file", NULL));
	return (false);
}
