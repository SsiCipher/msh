/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.redo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:48:26 by yanab             #+#    #+#             */
/*   Updated: 2022/08/24 10:56:40 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * find and replace all variables in str
 * 
 * @param	str the string to use
 * @param	env t_env struct containing environment variables
 * @return	str string with variables replaced with their values
 */
t_token	*expand_variables(t_token *tkn, bool ignore_quotes, t_env *env)
{
	int		i;
	char	*var;
	char	quote_type;
	char	*expanded_str;

	i = 0;
	quote_type = '\0';
	expanded_str = ft_strdup(tkn->content);
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
	free(tkn->content);
	tkn->content = expanded_str;
	return (tkn);
}

/**
 * get the files and directories that match pattern in path
 * 
 * @param	pattern the pattern to match
 * @param	path the path to search
 * @return	a string of names concatenated with space ' '
 */
t_token	*expand_wildcard(t_token *tkn, char *path)
{
	int		i;
	t_dir	*dir;
	t_token	*new_tkn;
	char	*pattern;

	i = -1;
	new_tkn = NULL;
	dir = read_dir_content(path);
	pattern = unquote_text(tkn->content);
	while (++i < dir->length)
	{
		if (match_wildcard(pattern, dir->content[i])
			&& !(pattern[0] != '.' && dir->content[i][0] == '.'))
		{
			if (!new_tkn)
				new_tkn = edit_token(tkn, dir->content[i], CMD);
			else
				new_tkn = insert_token(new_tkn, create_token(dir->content[i], CMD, ft_strlen(dir->content[i])));
		}
	}
	free_dir(&dir);
	free(pattern);
	if (!new_tkn)
		return (tkn);
	return (new_tkn);
}

/**
 * expand speacial characters ($, *) in tokens
 * 
 * @param	token_lst the list of tokens to expand
 * @param	env t_env struct that holds all the environment variables
 */
void	expand_shell(t_token *token_lst, t_env *env)
{
	t_token	*curr;

	curr = token_lst;
	while (curr)
	{
		if (ft_strchr(curr->content, '$'))
			curr = expand_variables(curr, false, env);
		else if (ft_strchr(curr->content, '*'))
			curr = expand_wildcard(curr, "./");
		curr = curr->next;
	}
}
