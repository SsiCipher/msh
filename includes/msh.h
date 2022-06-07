#ifndef MSH_H
# define MSH_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

typedef struct s_env
{
	char	**content;
	size_t	length;
}	t_env;

#endif
