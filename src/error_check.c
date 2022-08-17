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

/**
 * display a syntax error
 * 
 * @param	error the error to display
 * @param	token the token where the error occured
 * @return	always true
 */
bool	display_error(char *error, char *token)
{
	ft_putstr_fd("msh: syntax error: ", 2);
	ft_putstr_fd(error, 2);
	if (token)
	{
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("`", 2);
	}
	ft_putchar_fd('\n', 2);
	return (true);
}

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
		// Heredoc
		if (is_next_invalid(tkn, R_HEREDOC, CMD))
			return (display_error("unexpected token", "newline"));
		// Redirection
		else if (is_next_invalid(tkn, R_INPUT, CMD) || is_next_invalid(tkn, R_OUTPUT, CMD) || is_next_invalid(tkn, R_APPEND, CMD))
			return (display_error("unexpected token", "newline"));
		// Logical AND/OR
		else if (
			(is_both_invalid(tkn, OR, CMD) && is_next_invalid(tkn, OR, O_PARENTH) && is_prev_invalid(tkn, OR, C_PARENTH))
			|| (is_both_invalid(tkn, AND, CMD) && is_next_invalid(tkn, AND, O_PARENTH) && is_prev_invalid(tkn, AND, C_PARENTH))
		)
			return (display_error("unexpected token", tkn->content));
		// Pipe
		else if (
			is_both_invalid(tkn, PIPE, CMD) && is_next_invalid(tkn, PIPE, R_HEREDOC) && is_prev_invalid(tkn, PIPE, C_PARENTH)
			&& is_next_invalid(tkn, PIPE, R_INPUT) && is_next_invalid(tkn, PIPE, R_OUTPUT) && is_next_invalid(tkn, PIPE, R_APPEND)
		)
			return (display_error("unexpected token", tkn->content));
		// Quotes
		else if (tkn->type == CMD && is_quotes_unclosed(tkn->content))
			return (display_error("unexpected end of file", NULL));
		// Parenthesis
		else if (tkn->type == O_PARENTH)
		{
			if (
				is_next_invalid(tkn, O_PARENTH, CMD)
				&& is_next_invalid(tkn, PIPE, R_INPUT) && is_next_invalid(tkn, PIPE, R_OUTPUT) && is_next_invalid(tkn, PIPE, R_APPEND)
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
