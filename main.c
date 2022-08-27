/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:11:27 by yanab             #+#    #+#             */
/*   Updated: 2022/08/27 05:20:19 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	g_exit_code = 0;

char	*create_prompt_str(t_env *env)
{
	char	*prompt;
	char	*user;
	char	*cwd;

	user = get_var(env, "USER");
	if (!user)
		user = ft_strdup("MINISHELL");
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = get_var(env, "PWD");
	prompt = ft_multijoin(5,
			"\e[1;32m", user, " • \e[1;36m\x1B[1;34m", cwd, "\x1B[0m » ");
	free(user);
	free(cwd);
	return (prompt);
}

char	*init_shell(t_env *env)
{
	char	*prompt;
	char	*shell;

	prompt = create_prompt_str(env);
	shell = readline(prompt);
	free(prompt);
	add_history(shell);
	return (shell);
}

void	increment_shlvl(t_env *env)
{
	char	*shlvl;
	int		lvl;

	shlvl = get_var(env, "SHLVL");
	lvl = ft_atoi(shlvl);
	free(shlvl);
	shlvl = ft_itoa(lvl + 1);
	edit_var(env, "SHLVL", shlvl, false);
	free(shlvl);
}

void	start_repl(t_env *env)
{
	char		*shell;
	t_token		*tokens_lst;
	t_node		*ast_tree;

	while (true)
	{
		ast_tree = NULL;
		shell = init_shell(env);
		if (!shell)
			continue ;
		tokens_lst = create_tokens_list(shell);
		expand_shell(tokens_lst, env);
		if (tokens_lst && !check_errors(tokens_lst))
		{
			handle_heredocs(tokens_lst, env);
			printf("> ------- Tokens ------- <\n\n");
			print_tokens(tokens_lst);
			ast_tree = create_ast(tokens_lst);
			printf("\n> ------- AST ------- <\n\n");
			print_tree(ast_tree, 0);
		}
		free_tree(ast_tree);
		free_tokens(&tokens_lst);
		free(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;

	(void)argc;
	(void)argv;
	env = create_env(envp);
	increment_shlvl(env);
	start_repl(env);
	return (0);
}
