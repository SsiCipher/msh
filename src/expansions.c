/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:48:26 by yanab             #+#    #+#             */
/*   Updated: 2022/08/27 05:25:04 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

// TODO: expand $? to be the value of the global variable exit_code

/**
 * Expand variables in token
 * 
 * @param	tkn the token to use for the expansion
 * @param	env t_env struct containing environment variables
 * @return	the token used
 */
t_token	*expand_tkn_vars(t_token *tkn, t_env *env)
{
	tkn->content = expand_vars(tkn->content, false, env);
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
	free(str);
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
// TODO: handle mixed expansions -> *$VAR => expand * if VAR doesn't exist

/**
 * Get the files and directories that match pattern in path
 * 
 * @param	path the token to use for the expansion
 * @param	pattern the pattern to match
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

/**
 * Unquote all tokens content
 * 
 * @param	tkn_lst the head of the token list 
 */
void	unquote_tokens(t_token *tkn_lst)
{
	t_token	*curr_tkn;
	char	*tmp;

	curr_tkn = tkn_lst;
	while (curr_tkn)
	{
		if (
			(curr_tkn->prev && curr_tkn->prev->type != R_HEREDOC)
			&& !ft_strchr(curr_tkn->content, '*')
		)
		{
			tmp = curr_tkn->content;
			curr_tkn->content = unquote_text(curr_tkn->content);
			free(tmp);
		}
		curr_tkn = curr_tkn->next;
	}
}

/**
 * Expand speacial characters ($, *) in tokens
 * 
 * @param	token_lst the list of tokens to expand
 * @param	env t_env struct that holds all the environment variables
 */
void	expand_shell(t_token *token_lst, t_env *env)
{
	t_token	*curr;
	char	*wildcard_pattern;
	bool	is_limiter;

	curr = token_lst;
	while (curr)
	{
		is_limiter = (curr->prev && curr->prev->type == R_HEREDOC);
		if (ft_strchr(curr->content, '$') && !is_limiter)
			curr = expand_tkn_vars(curr, env);
		else if (ft_strchr(curr->content, '*') && !is_limiter)
		{
			wildcard_pattern = unquote_text(curr->content);
			curr = expand_wildcard(curr, wildcard_pattern);
			free(wildcard_pattern);
		}
		curr = curr->next;
	}
	unquote_tokens(token_lst);
}
