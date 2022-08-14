/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:27:48 by yanab             #+#    #+#             */
/*   Updated: 2022/08/14 16:22:13 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <errno.h>
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
// # include <stdint.h>

# include "libft.h"

typedef enum e_type {
	OR,
	AND,
	CMD,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	R_HEREDOC,
	R_INPUT,
	R_OUTPUT,
	R_APPEND,
	O_PARENTH,
	C_PARENTH
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

typedef struct s_ast_node
{
	t_type				type;
	char				**argv;
	int					argc;
	bool				unlink_infile;
	int					input_fd;
	int					output_fd;
	int					exit_code;

	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

// =================== src/lexer.c

t_type		tkn_type(char *str);
int			tkn_length(t_type type);
t_token		*create_tokens_list(char *shell);

// =================== src/env.c

t_env		*create_env(char **envp);
void		delete_env(t_env **env);
char		*get_var(t_env *env, char *name);
bool		contains_var(t_env *env, char *name);
void		add_var(t_env *env, char *name, char *value);
void		edit_var(t_env *env, char *name, char *value, bool append);
void		delete_var(t_env *env, char *name);

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

// =================== src/tree.c

t_ast_node	*create_node(t_type type);
void		node_argv_push(t_ast_node *node, char *new_arg);
void		update_io_fds(t_ast_node *node, t_type type, char *filename);
t_ast_node	*create_ast(t_token *tkns_lst);

// =================== src/utils.c

void		toggle_quote(char curr_char, char *quote_type);
char		*unquote_text(char *str);

// =================== src/builtins.c

void		ft_echo(int argc, char **argv);
void		ft_cd(int argc, char **argv, t_env *env);
void		ft_pwd(int argc, char **argv);
void		ft_export(int argc, char **argv, t_env *env);
void		ft_unset(int argc, char **argv, t_env *env);
void		ft_env(int argc, char **argv, t_env *env);
void		ft_exit(int argc, char **argv, t_env *env);

// =================== src/debug.c

char		*get_type_name(t_type type);
void		print_tokens(t_token *tokens_lst);
void		print_node(t_ast_node *node);
void		print_tree(t_ast_node *root, int level);

#endif
