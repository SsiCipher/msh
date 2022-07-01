/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:27:48 by yanab             #+#    #+#             */
/*   Updated: 2022/07/01 12:05:42 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef enum e_type {
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
}	t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	int				length;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char		**content;
	size_t		length;
}	t_env;

typedef struct s_dir
{
	char	**content;
	int		length;
}	t_dir;

typedef struct s_ast
{
	t_type			type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// =================== src/env.c

t_env		*copy_env(char **envp);
void		free_env(t_env **env);
char		*get_env_var(t_env *env, char *var_name);

// =================== src/lst.c

t_token		*create_token(char *content, t_type type, int length);
void		push_token(t_token **tokens_lst, t_token *new_token);
void		delete_token(t_token *token);
t_token		*last_token(t_token *tokens_lst);
void		free_tokens(t_token **tokens_lst);

// =================== src/parser.c

t_type		tkn_type(char *str);
bool		is_meta_char(t_type type);
int			tkn_length(t_type type);
t_token		*parse_shell(char *str);

// =================== src/expantions.c

char		*expand_vars(char *str, t_env *env);
char		*expand_wildcard(char *pattern, char *path);
void		expand_shell(t_token *token_lst, t_env *env);

// =================== src/expantions_utils.c

char		*ft_find_n_replace(char *str, char *find, char *replace);
char		*extract_var(char *str);
void		replace_var(char **str, char *var, t_env *env);
t_dir		*read_dir_content(char *dir_path);
bool		match_wildcard(char *pattern, char *text);

// =================== src/handle_here_doc.c

void		handle_here_docs(t_token *token_lst, t_env *env);
char		*remove_quotes(char *limiter);

// =================== src/error_check.c

bool		print_error(char *error_type, char *expected, char *tkn_content);
bool		check_errors(t_token *token_lst);

#endif
