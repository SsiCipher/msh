#include "msh.h"
#include <sys/types.h>
#include <dirent.h>

typedef struct s_dir
{
	char	**content;
	int		length;
}	t_dir;

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
		dir->content = ft_realloc(dir->content, sizeof(char *) * dir->length,
				sizeof(char *) * (dir->length + 1));
		dir->content[dir->length] = ft_strdup(dir_struct->d_name);
		dir->length += 1;
		dir_struct = readdir(dir_stream);
	}
	dir->content = ft_realloc(dir->content, sizeof(char *) * dir->length,
			sizeof(char *) * (dir->length + 1));
	dir->content[dir->length] = NULL;
	closedir(dir_stream);
	return (dir);
}

/**
 * check if the given string matches the patten
 * @param pattern pattern to match
 * @param string string to check
 * @return non-zero if the string matches the string else zero
 */
int	ft_ismatch(char *pattern, char *string)
{
	(void)pattern;
	(void)string;

	int n = text.size();
   	int m = pattern.size();

   	if (m == 0)    //when pattern is empty
    	return (n == 0);

   int i = 0, j = 0, textPointer = -1, pattPointer = -1;
   while (i < n) {
      if (text[i] == pattern[j]) {    //matching text and pattern characters
         i++;
         j++;
      }else if (j < m && pattern[j] == '?') {    //as ? used for one character
         i++;
         j++;
      }else if (j < m && pattern[j] == '*') {    //as * used for one or more character
         textPointer = i;
         pattPointer = j;
         j++;
      }else if (pattPointer != -1) {
         j = pattPointer + 1;
         i = textPointer + 1;
         textPointer++;
      }else
         return false;
   }

   while (j < m && pattern[j] == '*') {
      j++;     //j will increase when wildcard is *
   }

   if (j == m) {    //check whether pattern is finished or not
      return true;
   }

   return false;

	return (1);
}

int	main(void)
{
	t_dir	*dir;
	int		i;

	i = -1;
	dir = read_dir_content("./");
	while (dir->content[++i])
	{
		if (ft_ismatch("*.c", dir->content[i]))
			printf("%s\n", dir->content[i]);
	}

	return (0);
}
