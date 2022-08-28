/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:54:46 by yanab             #+#    #+#             */
/*   Updated: 2022/08/28 22:47:46 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * extract a variable from a string
 * 
 * @param	str the string to extraxt from
 * @return	the variable name | NULL if it's just a '$'
 */
char	*extract_var(char *str)
{
	int		name_len;

	name_len = 0;
	while (
		(!ft_isdigit(str[1]) && ft_isalnum(str[name_len + 1]))
		|| str[name_len + 1] == '_'
	)
		name_len++;
	if (ft_isdigit(str[1]))
		name_len++;
	if (name_len == 0)
	{
		if (str[name_len + 1] == '?')
			name_len = 1;
		else
			return (NULL);
	}
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
	if (!ft_strncmp(var, "$?", 2))
		var_value = ft_itoa(g_exit_code);
	else
		var_value = get_var(env, var + 1);
	temp = *str;
	*str = ft_find_n_replace(*str, start, var, var_value);
	free(temp);
	free(var_value);
	return (ft_strlen(var));
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
	ft_qsort_str(dir->content, dir->length, ft_strcmp);
	return (dir);
}

/**
 * Free all memory occupied by t_dir struct and set it to NULL
 * 
 * @param	dir the t_dir struct to free
 */
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
	int		i;
	int		j;
	int		text_p;
	int		patt_p;

	i = 0;
	j = 0;
	text_p = -1;
	patt_p = -1;
	if (*pattern == '\0')
		return (*text == '\0');
	while (text[i])
	{
		if (pattern[j] && pattern[j] == '*')
		{
			text_p = i;
			patt_p = j++;
		}
		else if (
			(text[i] == pattern[j])
			|| (pattern[i] == '\\' && pattern[i + 1] == '*' && text[j] == '*')
		)
		{
			i++;
			j++;
		}
		else if (patt_p != -1)
		{
			i = ++text_p;
			j = patt_p + 1;
		}
		else
			return (false);
	}
	while (pattern[j] && pattern[j] == '*')
		j++;
	return (pattern[j] == '\0');
}
