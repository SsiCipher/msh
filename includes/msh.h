/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:27:48 by yanab             #+#    #+#             */
/*   Updated: 2022/10/06 22:36:02 by yanab            ###   ########.fr       */
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
# include <sys/wait.h>

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

typedef struct s_node
{
	t_type				type;
	char				**argv;
	int					argc;
	bool				is_infile_heredoc;
	int					input_fd;
	int					output_fd;
	int					exit_code;

	struct s_node		*left;
	struct s_node		*right;
}	t_node;

extern int	g_exit_code;

/* ==========<< src/execution/exec.c >>========== */

int			exec_ast(t_node *node, t_env *env);

/* ==========<< src/execution/exec_single_cmd.c >>========== */

char		*get_cmd_path(char *cmd_name, t_env *env);
bool		is_builtin(char *cmd);
int			run_builtin(t_node *node, t_env *env);
void		_run_cmd(t_node *node, t_env *env, int tmp_io[2]);
int			run_cmd(t_node *node, t_env *env);

/* ==========<< src/execution/exec_utils.c >>========== */

void		print_err(char *error_msg, char *arg);
void		dup_io(t_node *node, int tmp_io[2]);
void		dup_pipe(int pipe_ends[2], int std_fd);
void		close_io(t_node *node, int tmp_io[2]);

/* ==========<< src/ast_tree_utils.c >>========== */

t_node		*create_node(t_type type);
void		free_tree(t_node *root);
void		node_argv_push(t_node *node, char *new_arg);
void		update_io_fds(t_node *node, t_type type, char *filename);

/* ==========<< src/ast_tree.c >>========== */

t_node		*create_ast(t_token *tkns_lst);

/* ==========<< src/builtins.c >>========== */

int			print_builtin_error(char *cmd, char *pre, char *error, int exit_code);
int			ft_echo(int argc, char **argv, t_env *env);
int			ft_cd_goto(char *path, t_env *env);
int			ft_cd(int argc, char **argv, t_env *env);
int			ft_pwd(int argc, char **argv, t_env *env);
bool		parse_var(char *line, char **name, char **value);
bool		check_name(char *name);
void		ft_export_list(t_env *env);
int			ft_export(int argc, char **argv, t_env *env);
int			ft_unset(int argc, char **argv, t_env *env);
int			ft_env(int argc, char **argv, t_env *env);
long long	atoi_check(char *number);
int			ft_exit(int argc, char **argv, t_env *env);

/* ==========<< src/debug.c >>========== */

char		*get_type_name(t_type type);
void		print_tokens(t_token *tokens_lst);
void		print_node(t_node *node);
void		print_tree(t_node *root, int level);

/* ==========<< src/env.c >>========== */

t_env		*create_env(char **envp);
void		free_env(t_env **env);
bool		is_var(char *env_line, char *name);
bool		contains_var(t_env *env, char *name);

/* ==========<< src/env_ops.c >>========== */

char		*get_var(t_env *env, char *name);
void		add_var(t_env *env, char *name, char *value);
void		edit_var(t_env *env, char *name, char *value, bool append);
void		delete_var(t_env *env, char *name);

/* ==========<< src/error_check.c >>========== */

bool		check_redirection(t_token *tkn);
bool		check_logical_and_or(t_token *tkn);
bool		check_pipe(t_token *tkn);
bool		check_parenthesis(t_token *tkn, bool *is_inside_parenth);
bool		check_errors(t_token *tkn);

/* ==========<< src/error_check_utils.c >>========== */

bool		print_error(char *error, char *type, char *token);
bool		is_next_valid(t_token *curr_tkn, t_type curr_type,
				t_type next_type);
bool		is_prev_valid(t_token *curr_tkn, t_type curr_type,
				t_type prev_type);
bool		is_both_valid(t_token *curr_tkn, t_type curr_type,
				t_type valid_type);
bool		is_quotes_unclosed(char *str);

/* ==========<< src/expansions.c >>========== */

t_token		*expand_tkn_vars(t_token *tkn, t_env *env);
char		*expand_vars(char *str, bool ignore_quotes, t_env *env);
t_token		*expand_wildcard(t_token *tkn, char *path);
void		unquote_tokens(t_token *tkn_lst);
void		expand_shell(t_token *token_lst, t_env *env);

/* ==========<< src/expansions_utils.c >>========== */

char		*extract_var(char *str);
int			replace_var(char **str, int start, char *var, t_env *env);
t_dir		*read_dir_content(char *dir_path);
void		free_dir(t_dir **dir);
bool		match_wildcard(char *pattern, char *text);

/* ==========<< src/heredoc.c >>========== */

int			open_heredoc_file(t_env *env, char **file_path);
char		*start_heredoc(char *limiter, bool is_limiter_quoted, t_env *env);
void		handle_heredocs(t_token *tkn, t_env *env);

/* ==========<< src/lexer.c >>========== */

t_type		tkn_type(char *str);
int			tkn_length(t_type type);
int			extract_cmd(char *shell, int i, t_token **lst, bool *is_quoted);
t_token		*create_tokens_list(char *shell);

/* ==========<< src/token.c >>========== */

t_token		*create_token(char *content, t_type type, int length);
void		push_token(t_token **tokens_lst, t_token *new_token);
t_token		*insert_token(t_token *target_token, t_token *new_token);
void		free_tokens(t_token **tokens_lst);
t_token		*edit_token(t_token *tkn, char *content, t_type type);

/* ==========<< src/utils.c >>========== */

void		toggle_quote(char c, char *quote_type, bool *is_quoted);
char		*unquote_text(char *str, bool escape_wildcard);

#endif
