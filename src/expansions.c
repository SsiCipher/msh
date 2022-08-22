/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:48:26 by yanab             #+#    #+#             */
/*   Updated: 2022/08/22 10:12:52 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

// TODO: expand $? to the latest exit_code

/**
 * find and replace all variables in str
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

/**
 * get the files and directories that match pattern in path
 * 
 * @param	pattern the pattern to match
 * @param	path the path to search
 * @return	a string of names concatenated with space ' '
 */
void	expand_wildcard(t_token *tkn, char *path)
{
	int		i;
	t_dir	*dir;
	char	*pattern;

	i = -1;
	dir = read_dir_content(path);
	pattern = unquote_text(tkn->content);
	while (dir->content[++i])
	{
		if (match_wildcard(pattern, dir->content[i]) && !(pattern[0] != '.' && dir->content[i][0] == '.'))
			insert_token(tkn, create_token(dir->content[i], CMD, ft_strlen(dir->content[i])));
	}
	free(pattern);
	delete_token(tkn);
	free_dir(&dir);
}

// char	*expand_wildcard(char *pattern, char *path)
// {
// 	int		i;
// 	t_dir	*dir;
// 	char	*tmp;
// 	char	*output;

// 	i = -1;
// 	output = ft_strdup("");
// 	dir = read_dir_content(path);
// 	pattern = unquote_text(pattern);
// 	while (dir->content[++i])
// 	{
// 		if (match_wildcard(pattern, dir->content[i])
// 			&& !(pattern[0] != '.' && dir->content[i][0] == '.'))
// 		{
// 			tmp = output;
// 			if (*output == '\0')
// 				output = ft_strdup(dir->content[i]);
// 			else
// 				output = ft_strjoin_many(3, output, " ", dir->content[i]);
// 			free(tmp);
// 		}
// 	}
// 	free(pattern);
// 	free_dir(&dir);
// 	return (output);
// }

void	unquote_tokens(t_token *token_lst)
{
	char	*tmp;

	while (token_lst)
	{
		tmp = token_lst->content;
		token_lst->content = unquote_text(token_lst->content);
		free(tmp);
		token_lst = token_lst->next;
	}
}

// xTODO: Don't expand heredoc limiter
// xTODO: expand * to separate tokens
// TODO: Don't expand "*"

/**
 * expand speacial characters ($, *) in tokens
 * 
 * @param	token_lst the list of tokens to expand
 * @param	env t_env struct that holds all the environment variables
 */
void	expand_shell(t_token *token_lst, t_env *env)
{
	char	*tmp;
	t_token	*curr;
	bool	is_cmd;

	curr = token_lst;
	while (curr)
	{
		tmp = curr->content;
		is_cmd = (curr->type == CMD
				&& (!curr->prev
					|| (curr->prev && curr->prev->type != R_HEREDOC)));
		if (is_cmd && ft_strchr(curr->content, '$'))
		{
			curr->content = expand_vars(curr->content, false, env);
			free(tmp);
		}
		else if (is_cmd && ft_strchr(curr->content, '*'))
		{
			expand_wildcard(curr, "./");
		}
		curr = curr->next;
	}
	unquote_tokens(token_lst);
}
