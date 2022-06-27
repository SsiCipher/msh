/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:48:26 by yanab             #+#    #+#             */
/*   Updated: 2022/06/27 06:01:59 by yanab            ###   ########.fr       */
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
	int		var_len;
	char	*var;
	char	*var_value;

	i = 0;
	while (str[i])
	{
		var_len = 0;
		if (str[i] == '$')
		{
			i += 1;
			while (
				ft_isalnum(str[i + var_len])
				|| str[i + var_len] == '_'
			)
				var_len += 1;
			if (var_len == 0)
				i++;
			else
			{
				var = ft_substr(str, i - 1, var_len + 1);
				var_value = get_env_var(env, var + 1);
				str = ft_find_n_replace(str, var, var_value);
				free(var);
				free(var_value);
				i += var_len;
			}
		}
		else
			i++;
	}
	return (str);
}

int	cmp_names(const void *p1, const void *p2)
{
	return (
		ft_strcasecmp(*(const char **)p1, *(const char **)p2)
	);
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
	qsort(dir->content, dir->length, sizeof(char *), cmp_names);
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
	t_token	*t;
	char	*tmp;

	t = token_lst;
	while (t)
	{
		if (
			(t->type == DOUBLE_QUOTE || t->type == SIMPLE_CMD)
			&& ft_memchr(t->content, '$', t->length)
		)
		{
			tmp = t->content;
			t->content = expand_vars(t->content, env);
			free(tmp);
		}
		else if (
			t->type == SIMPLE_CMD
			&& ft_memchr(t->content, '*', t->length)
		)
		{
			tmp = t->content;
			t->content = expand_wildcard(t->content, "./");
			free(tmp);
		}
		t = t->next;
	}
}
