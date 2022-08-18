/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:56:26 by yanab             #+#    #+#             */
/*   Updated: 2022/08/18 08:33:32 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Display a syntax error
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

/**
 * Check if the next token is valid
 * 
 * @param	curr_tkn the current token
 * @param	curr_type the current token type
 * @param	next_type the next token's expected type
 * @return	true if the next token is of type 'next_type', false otherwise
 */
bool	is_next_invalid(t_token *curr_tkn, t_type curr_type, t_type next_type)
{
	return (
		curr_tkn->type == curr_type
		&& (!curr_tkn->next || curr_tkn->next->type != next_type)
	);
}

/**
 * Check if the previous token is valid
 * 
 * @param	curr_tkn the current token
 * @param	curr_type the current token type
 * @param	prev_type the previous token's expected type
 * @return	true if the previous token is of type 'prev_type', false otherwise
 */
bool	is_prev_invalid(t_token *curr_tkn, t_type curr_type, t_type prev_type)
{
	return (
		curr_tkn->type == curr_type
		&& (!curr_tkn->prev || curr_tkn->prev->type != prev_type)
	);
}

/**
 * Check if both surronding tokens are valid
 * 
 * @param	curr_tkn the current token
 * @param	curr_type the current token type
 * @param	valid_type both token's expected type
 * @return	true if the both token is of type 'expected_type', false otherwise
 */
bool	is_both_invalid(t_token *curr_tkn, t_type curr_type, t_type valid_type)
{
	return (
		is_prev_invalid(curr_tkn, curr_type, valid_type)
		|| is_next_invalid(curr_tkn, curr_type, valid_type)
	);
}

/**
 * Check if quotes in string are unclosed
 * 
 * @param	str the string to check
 * @return	true if the string has unclosed quotes, false otherwise
 */
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
