/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:48:26 by yanab             #+#    #+#             */
/*   Updated: 2022/08/25 09:14:16 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Expand variables in token
 * 
 * @param	tkn the token to use for the expansion
 * @param	env t_env struct containing environment variables
 * @return	the token used
 */
t_token	*expand_variables(t_token *tkn, t_env *env)
{
	char	*tmp;

	tmp = tkn->content;
	tkn->content = expand_vars(tkn->content, false, env);
	free(tmp);
	return (tkn);
}

/**
 * Find and replace all variables in str
 * 
 * @param	str the string to use
 * @param	env t_env struct containing environment variables
 * @return	str string with variables replaced with their values
 */
char	*expand_vars(char *str, bool ignore_quotes, t_env *env)
{
	int		i;
	char	*var;
	char	quote_type;
	char	*expanded_str;

	i = 0;
	quote_type = '\0';
	expanded_str = ft_strdup(str);
	while (expanded_str[i])
	{
		toggle_quote(expanded_str[i], &quote_type, NULL);
		if (expanded_str[i] != '$' || (!ignore_quotes && quote_type == '\''))
			i += 1;
		else
		{
			var = extract_var(&expanded_str[i]);
			i += replace_var(&expanded_str, i, var, env);
			free(var);
		}
	}
	return (expanded_str);
}

// TODO: match quoted * as a literal character

/**
 * get the files and directories that match pattern in path
 * 
 * @param	pattern the pattern to match
 * @param	path the path to search
 * @return	a string of names concatenated with space ' '
 */
t_token	*expand_wildcard(t_token *tkn, char *pattern)
{
	int		i;
	t_dir	*dir;
	char	*file;
	t_token	*new_tkn;

	i = -1;
	new_tkn = NULL;
	dir = read_dir_content("./");
	while (++i < dir->length)
	{
		file = dir->content[i];
		if (match_wildcard(pattern, file)
			&& !(pattern[0] != '.' && file[0] == '.'))
		{
			if (!new_tkn)
				new_tkn = edit_token(tkn, file, CMD);
			else
				new_tkn = insert_token(new_tkn,
						create_token(file, CMD, ft_strlen(file)));
		}
	}
	free_dir(&dir);
	if (!new_tkn)
		return (tkn);
	return (new_tkn);
}

// TODO: handle mixed expansions -> *$VAR => expand * if VAR doesn't exist

/**
 * expand speacial characters ($, *) in tokens
 * 
 * @param	token_lst the list of tokens to expand
 * @param	env t_env struct that holds all the environment variables
 */
void	expand_shell(t_token *token_lst, t_env *env)
{
	t_token	*curr;
	char	*wildcard_pattern;

	curr = token_lst;
	while (curr)
	{
		if (ft_strchr(curr->content, '$'))
			curr = expand_variables(curr, env);
		else if (ft_strchr(curr->content, '*'))
		{
			wildcard_pattern = unquote_text(curr->content);
			curr = expand_wildcard(curr, wildcard_pattern);
			free(wildcard_pattern);
		}
		curr = curr->next;
	}
}
