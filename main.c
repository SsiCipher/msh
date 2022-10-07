/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:11:27 by yanab             #+#    #+#             */
/*   Updated: 2022/10/06 22:38:10 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		g_exit_code = EXIT_SUCCESS;

void	increment_shlvl(t_env *env)
{
	char	*shlvl;
	int		lvl;

	shlvl = get_var(env, "SHLVL");
	if (shlvl)
		lvl = ft_atoi(shlvl);
	else
		lvl = 0;
	free(shlvl);
	if (lvl < 999)
		shlvl = ft_itoa(lvl + 1);
	else
		shlvl = ft_strdup("");
	edit_var(env, "SHLVL", shlvl, false);
	free(shlvl);
}

char	*init_prompt_str(t_env *env)
{
	char	*cwd;
	char	*user;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = get_var(env, "PWD");
	user = get_var(env, "USER");
	if (!user)
		user = ft_strdup("MINISHELL");
	prompt = ft_multijoin(5,
			"\e[1;32m", user, " • \e[1;36m\x1B[1;34m", cwd, "\x1B[0m » ");
	free(user);
	free(cwd);
	return (prompt);
}

char	*read_shell(t_env *env)
{
	char	*prompt;
	char	*shell;

	prompt = init_prompt_str(env);
	shell = readline(prompt);
	free(prompt);
	add_history(shell);
	return (shell);
}

void	msh_repl(t_env *env)
{
	char		*shell;
	t_token		*tokens_lst;
	t_node		*ast_tree;

	while (true)
	{
		ast_tree = NULL;
		shell = read_shell(env);
		if (shell && shell[0])
		{
			tokens_lst = create_tokens_list(shell);
			expand_shell(tokens_lst, env);
			if (tokens_lst && !check_errors(tokens_lst))
			{
				handle_heredocs(tokens_lst, env);
				ast_tree = create_ast(tokens_lst);
				g_exit_code = exec_ast(ast_tree, env);
			}
			free(shell);
			free_tree(ast_tree);
			free_tokens(&tokens_lst);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;

	(void)argc;
	(void)argv;
	env = create_env(envp);
	increment_shlvl(env);
	printf("PID: [%d]\n", getpid());
	msh_repl(env);
	free_env(&env);
	return (0);
}
