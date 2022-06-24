#ifndef MSH_H
# define MSH_H

# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "get_next_line.h"

typedef struct s_env
{
	char		**content;
	size_t		length;
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
	SIMPLE_CMD,
	OPEN_QUOTE,
	CLOSE_QUOTE
}	t_token_types;

typedef struct s_token
{
	char			*content;
	t_token_types	type;
	int				length;
	struct s_token	*next;
}	t_token;

typedef struct s_dir
{
	char	**content;
	int		length;
}	t_dir;

typedef struct s_ast
{
	t_token_types	type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// =================== src/env.c

t_env			*copy_env(char **envp);
void			free_env(t_env **env);
char			*get_env_var(t_env *env, char *var_name);

// =================== src/parse.c

t_token_types	get_t_type(char *str);
int				get_t_length(t_token_types type);
t_token			*create_token(char *content, t_token_types type, int length);
void			push_token(t_token **lst, t_token *new_token);
void			free_all_tokens(t_token **tokens_lst);
void			tokenize_shell(char *str, t_token **tokens);

// =================== src/var_expantion.c

char			*ft_find_n_replace(char *str, char *find, char *replace);
char			*expand_vars(char *str, t_env *env);

// =================== src/star_expantion.c

t_dir			*read_dir_content(char *dir_path);
bool			match_wildcard(char *pattern, char *text);
char			*expand_wildcard(char *pattern, char *path);

// =================== src/error_check.c

bool			check_errors(t_token *token_lst);

// =================== src/handle_here_doc.c

void			handle_here_docs(t_token *token_lst, t_env *env);

// =================== src/tokenize.c

t_token		*parse_shell(char *shell);

#endif
