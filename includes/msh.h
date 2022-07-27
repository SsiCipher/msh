/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:27:48 by yanab             #+#    #+#             */
/*   Updated: 2022/07/24 17:45:36 by cipher           ###   ########.fr       */
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

typedef enum e_type {
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	HERE_DOC,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	PIPE,
	AND,
	OR,
	CMD,
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*content;
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

// =================== src/lexer.c

t_type		tkn_type(char *str);
int			tkn_length(t_type type);
t_token		*create_tokens_list(char *shell);

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

t_token		*parse_shell(char *str);

// =================== src/expantions.c

char		*expand_vars(char *str, t_env *env);
char		*expand_wildcard(char *pattern, char *path);
void		expand_shell(t_token *token_lst, t_env *env);

// =================== src/expantions_utils.c

char		*extract_var(char *str);
char		*ft_find_n_replace(char *str, int start_i, char *find, char *replace);
int			replace_var(char **str, int start, char *var, t_env *env);
t_dir		*read_dir_content(char *dir_path);
bool		match_wildcard(char *pattern, char *text);

// =================== src/handle_here_doc.c

void		toggle_quote(char curr_char, char *quote_type);

// =================== src/handle_here_doc.c

void		handle_here_docs(t_token *token_lst, t_env *env);
char		*remove_quotes(char *limiter);

// =================== src/error_check.c

bool		print_error(char *error_type, char *expected, char *tkn_content);
bool		check_errors(t_token *token_lst);

// =================== src/error_check.c

char		*get_type_name(t_type type);

#endif
