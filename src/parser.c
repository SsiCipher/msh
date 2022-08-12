/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:33:46 by yanab             #+#    #+#             */
/*   Updated: 2022/08/12 07:36:49 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Get the type of the current token
 * 
 * @param	str the string to scan for tokens
 * @return	t_type enum value that refers to the token type
 */
t_type	tkn_type(char *str)
{
	if (!ft_strncmp(str, "'", 1))
		return (S_QUOTE);
	else if (!ft_strncmp(str, "\"", 1))
		return (D_QUOTE);
	if (!ft_strncmp(str, "<<", 2))
		return (R_HEREDOC);
	else if (!ft_strncmp(str, ">>", 2))
		return (R_APPEND);
	else if (!ft_strncmp(str, "<", 1))
		return (R_INPUT);
	else if (!ft_strncmp(str, ">", 1))
		return (R_OUTPUT);
	else if (!ft_strncmp(str, "&&", 2))
		return (AND);
	else if (!ft_strncmp(str, "||", 2))
		return (OR);
	else if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else
		return (CMD);
}

/**
 * Get the length of the token
 * 
 * @param	type the type of the token
 * @return	the length of the token
 */
int	tkn_length(t_type type)
{
	if (
		type == R_HEREDOC
		|| type == R_APPEND
		|| type == AND
		|| type == OR
	)
		return (2);
	return (1);
}

/**
 * Parse the given string into a token list
 * 
 * @param	str the string to parse
 * @return	the parsed tokens from the string
 */
t_token	*parse_shell(char *str)
{
	int			i;
	t_type		t;
	int			len;
	t_token		*tokens_lst;

	i = 0;
	tokens_lst = NULL;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		t = tkn_type(str + i);
		if (tokens_lst && last_token(tokens_lst)->type == R_HEREDOC)
		{
			len = 0;
			while (str[i + len] && !isspace(str[i + len]))
				len++;
			push_token(&tokens_lst, create_token(str + i, CMD, len));
			i += len;
		}
		else if (t == CMD)
		{
			len = 0;
			while (
				tkn_type(str + i + len) == CMD
				&& !ft_isspace(str[i + len]) && str[i + len] != '\0'
			)
				len++;
			push_token(&tokens_lst, create_token(str + i, CMD, len));
			i += len;
		}
		else
		{
			len = (t == S_QUOTE || t == D_QUOTE);
			while (
				tkn_type(&str[i + len]) != t
				&& str[i + len] != '\0'
			)
				len++;
			push_token(
				&tokens_lst,
				create_token(str + i, t, tkn_length(t) + len)
				);
			i += tkn_length(t) + len;
		}
	}
	return (tokens_lst);
}
