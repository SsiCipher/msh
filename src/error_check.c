/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:56:26 by yanab             #+#    #+#             */
/*   Updated: 2022/08/16 05:38:38 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

// TODO: better errors like bash

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

// TODO: check unclosed quotes and parenthesis
// TODO: fix norm errors

bool	is_next_invalid(t_token *curr_tkn, t_type curr_type, t_type next_type)
{
	return (
		curr_tkn->type == curr_type
		&& (!curr_tkn->next || curr_tkn->next->type != next_type)
	);
}

bool	is_prev_invalid(t_token *curr_tkn, t_type curr_type, t_type prev_type)
{
	return (
		curr_tkn->type == curr_type
		&& (!curr_tkn->prev || curr_tkn->prev->type != prev_type)
	);
}

bool	is_both_invalid(t_token *curr_tkn, t_type curr_type, t_type prev_type)
{
	return (
		is_prev_invalid(curr_tkn, curr_type, prev_type)
		|| is_next_invalid(curr_tkn, curr_type, prev_type)
	);
}

bool	is_quotes_unclosed(char *str)
{
	int		i;
	char	quote_type;

	i = -1;
	quote_type = '\0';
	while (str[++i])
		toggle_quote(str[i], &quote_type, NULL);
	return (quote_type != '\0');
}

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
			return (print_error("syntax", "limiter", tkn->content));
		else if (is_next_invalid(tkn, R_INPUT, CMD) || is_next_invalid(tkn, R_OUTPUT, CMD) || is_next_invalid(tkn, R_APPEND, CMD))
			return (print_error("syntax", "file", tkn->content));
		else if ((is_both_invalid(tkn, OR, CMD) && is_next_invalid(tkn, OR, O_PARENTH) && is_prev_invalid(tkn, OR, C_PARENTH)) || (is_both_invalid(tkn, AND, CMD) && is_next_invalid(tkn, AND, O_PARENTH) && is_prev_invalid(tkn, AND, C_PARENTH)))
			return (print_error("syntax", "command", tkn->content));
		else if (is_both_invalid(tkn, PIPE, CMD) && is_prev_invalid(tkn, PIPE, C_PARENTH) && is_next_invalid(tkn, PIPE, R_HEREDOC) && is_next_invalid(tkn, PIPE, R_INPUT) && is_next_invalid(tkn, PIPE, R_OUTPUT) && is_next_invalid(tkn, PIPE, R_APPEND))
			return (print_error("syntax", "command", tkn->content));
		else if (tkn->type == CMD && is_quotes_unclosed(tkn->content))
			return (print_error("syntax", "matching quote", NULL));
		else if (tkn->type == O_PARENTH)
		{
			if (is_next_invalid(tkn, O_PARENTH, CMD))
				return (print_error("syntax", "command", tkn->content));
			else
				is_inside_parenth = true;
		}
		else if (tkn->type == C_PARENTH)
		{
			if (is_inside_parenth)
				is_inside_parenth = false;
			else
				return (print_error("syntax", "matching parethesis", NULL));
		}
		tkn = tkn->next;
	}
	if (is_inside_parenth)
		return (print_error("syntax", "matching parethesis", NULL));
	return (false);
}
