#include "msh.h"

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

int cmp_names(const void* p1, const void* p2)
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
	return (output);
}
