/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:48:26 by yanab             #+#    #+#             */
/*   Updated: 2022/06/30 10:06:27 by yanab            ###   ########.fr       */
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
char	*expand_vars(char *str, t_env *env)
{
	int		i;
	char	*var;
	char	*expanded_str;

	i = 0;
	expanded_str = ft_strdup(str);
	while (expanded_str[i])
	{
		if (expanded_str[i] != '$')
			i += 1;
		else
		{
			var = extract_var(&expanded_str[i]);
			if (!var)
				i += 1;
			else
			{
				replace_var(&expanded_str, var, env);
				i += ft_strlen(var);
			}
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
char	*expand_wildcard(char *pattern, char *path)
{
	int		i;
	char	*output;
	t_dir	*dir;
	char	*temp;

	i = -1;
	output = NULL;
	dir = read_dir_content(path);
	while (dir->content[++i])
	{
		if (match_wildcard(pattern, dir->content[i]))
		{
			temp = output;
			if (!output)
				output = ft_strjoin_many(1, dir->content[i]);
			else
				output = ft_strjoin_many(3, output, " ", dir->content[i]);
			free(temp);
		}
	}
	i = -1;
	while (++i < dir->length)
		free(dir->content[i]);
	free(dir->content);
	free(dir);
	return (output);
}

/**
 * expand speacial characters ($, *) in tokens
 * 
 * @param	token_lst the list of tokens to expand
 * @param	env t_env struct that holds all the environment variables
 */
void	expand_shell(t_token *token_lst, t_env *env)
{
	char	*tmp;

	while (token_lst)
	{
		if (
			(token_lst->type == DOUBLE_QUOTE || token_lst->type == SIMPLE_CMD)
			&& ft_memchr(token_lst->content, '$', token_lst->length)
		)
		{
			tmp = token_lst->content;
			token_lst->content = expand_vars(token_lst->content, env);
			free(tmp);
		}
		else if (
			token_lst->type == SIMPLE_CMD
			&& ft_memchr(token_lst->content, '*', token_lst->length)
		)
		{
			tmp = token_lst->content;
			token_lst->content = expand_wildcard(token_lst->content, "./");
			free(tmp);
		}
		token_lst = token_lst->next;
	}
}
