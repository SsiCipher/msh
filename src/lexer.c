/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:31:18 by yanab             #+#    #+#             */
/*   Updated: 2022/08/18 08:16:32 by cipher           ###   ########.fr       */
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
	if (!ft_strncmp(str, "<<", 2))
		return (R_HEREDOC);
	else if (!ft_strncmp(str, ">>", 2))
		return (R_APPEND);
	else if (!ft_strncmp(str, "<", 1))
		return (R_INPUT);
	else if (!ft_strncmp(str, ">", 1))
		return (R_OUTPUT);
	else if (!ft_strncmp(str, "(", 1))
		return (O_PARENTH);
	else if (!ft_strncmp(str, ")", 1))
		return (C_PARENTH);
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
 * Tokenize the given string
 * 
 * @param	shell the line read from the user
 * @param	i the current index
 * @param	lst the list of tokens
 * @param	is_quoted a boolean reflecting quotation state
 * @return	the length of the extracted cmd token
 */
int	extract_cmd(char *shell, int i, t_token **lst, bool *is_quoted)
{
	int			len;
	char		quote_type;

	len = 0;
	*is_quoted = false;
	quote_type = '\0';
	while ((tkn_type(&shell[i + len]) == CMD || *is_quoted) && shell[i + len])
	{
		toggle_quote(shell[i + len], &quote_type, is_quoted);
		if (ft_isspace(shell[i + len]) && !(*is_quoted))
			break ;
		else
			len++;
	}
	push_token(lst, create_token(&shell[i], CMD, len));
	return (len);
}

/**
 * Tokenize the given string
 * 
 * @param	str the string to parse
 * @return	tokens extraxted from the string
 */
t_token	*create_tokens_list(char *shell)
{
	int			i;
	t_token		*lst;
	bool		is_quoted;
	t_type		curr_tkn_type;

	i = 0;
	lst = NULL;
	is_quoted = false;
	while (shell[i])
	{
		while (ft_isspace(shell[i]))
			i++;
		if (shell[i] == '\0')
			break ;
		curr_tkn_type = tkn_type(&shell[i]);
		if (curr_tkn_type != CMD && !is_quoted)
		{
			push_token(&lst, create_token(&shell[i], curr_tkn_type,
					tkn_length(curr_tkn_type)));
			i += tkn_length(curr_tkn_type);
		}
		else if (curr_tkn_type == CMD)
			i += extract_cmd(shell, i, &lst, &is_quoted);
	}
	return (lst);
}
