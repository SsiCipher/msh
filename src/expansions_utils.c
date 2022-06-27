/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:54:46 by yanab             #+#    #+#             */
/*   Updated: 2022/06/27 06:01:49 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * find and replace the first occurence of 'find' in str by 'replace'
 * 
 * @param	str the string to use
 * @param	find the search word
 * @param	replace the word to repleace it with
 * @return	the new string allocated in memory
 */
char	*ft_find_n_replace(char *str, char *find, char *replace)
{
	char	*find_i;
	char	*start;
	char	*end;
	char	*output;

	find_i = ft_strstr(str, find);
	start = ft_substr(str, 0, find_i - str);
	end = ft_substr(
			str,
			(unsigned int)(find_i - str) + ft_strlen(find),
			ft_strlen(str));
	output = ft_strjoin_many(3, start, replace, end);
	free(start);
	free(end);
	return (output);
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
	return (dir);
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
	if (j == m)
		return (true);
	return (false);
}
