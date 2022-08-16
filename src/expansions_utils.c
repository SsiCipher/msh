/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:54:46 by yanab             #+#    #+#             */
/*   Updated: 2022/08/16 03:48:41 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * extract a variable from a string
 * 
 * @param	str the string to extraxt from
 * @return	the variable of NULL if it's just a '$' 
 */
char	*extract_var(char *str)
{
	int		name_len;

	name_len = 0;
	while (
		ft_isalnum(str[name_len + 1])
		|| str[name_len + 1] == '_'
	)
		name_len++;
	if (name_len == 0)
		return (NULL);
	return (ft_substr(str, 0, name_len + 1));
}

/**
 * replace the given variable in a string
 * 
 * @param	str the string to use
 * @param	start index to start the replacement from
 * @param	var the variable to replace
 * @param	env t_env struct that holds all the environment variables
 * @return	the length of the variable replaced
 */
int	replace_var(char **str, int start, char *var, t_env *env)
{
	char	*temp;
	char	*var_value;

	if (!var)
		return (1);
	var_value = get_var(env, var + 1);
	temp = *str;
	*str = ft_find_n_replace(*str, start, var, var_value);
	free(temp);
	free(var_value);
	return (ft_strlen(var));
}

// TODO: change qsort to ft_qsort

int	cmp_names(const void *p1, const void *p2)
{
	return (
		ft_strcmp(*(const char **)p1, *(const char **)p2)
	);
}

/**
 * Read all the files in a directory into the t_dir struct
 * 
 * @param	dir_path the path to the directory
 * @return	pointer to t_dir struct
 */
t_dir	*read_dir_content(char *dir_path)
{
	DIR				*dir_stream;
	struct dirent	*dir_struct;
	t_dir			*dir;

	dir_stream = opendir(dir_path);
	dir_struct = readdir(dir_stream);
	dir = (t_dir *)malloc(sizeof(t_dir));
	dir->content = NULL;
	dir->length = 0;
	while (dir_struct)
	{
		dir->content = (char **)ft_realloc(dir->content,
				sizeof(char *) * dir->length,
				sizeof(char *) * (dir->length + 1));
		dir->content[dir->length] = ft_strdup(dir_struct->d_name);
		dir->length += 1;
		dir_struct = readdir(dir_stream);
	}
	dir->content = (char **)ft_realloc(dir->content,
			sizeof(char *) * dir->length, sizeof(char *) * (dir->length + 1));
	dir->content[dir->length] = NULL;
	closedir(dir_stream);
	qsort(dir->content, dir->length, sizeof(char *), cmp_names);
	return (dir);
}

void	free_dir(t_dir **dir)
{
	int	i;

	i = -1;
	while (++i < (*dir)->length)
		free((*dir)->content[i]);
	free((*dir)->content);
	free((*dir));
	*dir = NULL;
}

/**
 * check if the given string matches the patten
 * 
 * @param	pattern pattern to match
 * @param	text string to check
 * @return	'true' if the string matches the string else 'false'
 */
bool	match_wildcard(char *pattern, char *text)
{
	int		n;
	int		m;
	int		i;
	int		j;
	int		text_pointer;
	int		patt_pointer;

	n = ft_strlen(text);
	m = ft_strlen(pattern);
	i = 0;
	j = 0;
	text_pointer = -1;
	patt_pointer = -1;
	if (m == 0)
		return (n == 0);
	if (pattern[0] != '.' && text[0] == '.')
		return (false);
	while (i < n)
	{
		if (text[i] == pattern[j])
		{
			i++;
			j++;
		}
		else if (j < m && pattern[j] == '*')
		{
			text_pointer = i;
			patt_pointer = j;
			j++;
		}
		else if (patt_pointer != -1)
		{
			j = patt_pointer + 1;
			i = text_pointer + 1;
			text_pointer++;
		}
		else
			return (false);
	}
	while (j < m && pattern[j] == '*')
		j++;
	return (j == m);
}
