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

typedef enum e_token_types {
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HERE_DOC,
	REDIRECT_APPEND,
	PIPE,
	DOLLAR_SIGN,
	AND,
	OR,
	ASTERISK,
	SIMPLE_CMD
}	t_token_types;

typedef struct s_token
{
	char			*content;
	t_token_types	type;
	int				length;
	struct s_token	*next;
}	t_token;

t_env	*dup_env(char **envp);
char *get_env_var(t_env *env, char *var_name);

#endif
