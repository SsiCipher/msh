/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:11:27 by yanab             #+#    #+#             */
/*   Updated: 2022/08/12 08:23:53 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*create_prompt_str(t_env *env)
{
	char	*prompt;
	char	*user;
	char	*cwd;

	user = get_var(env, "USER");
	if (!user)
		user = ft_strdup("MINISHELL");
	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin_many(
			5,
			"\e[1;32m", user, " • \e[1;36m\x1B[1;34m", cwd, "\x1B[0m » "
			);
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

void	run_builtin(int argc, char **argv, t_env *env)
{
	if (!ft_strcmp(argv[0], "echo"))
		ft_echo(argc, argv);
	else if (!ft_strcmp(argv[0], "cd"))
		ft_cd(argc, argv, env);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(argc, argv);
	else if (!ft_strcmp(argv[0], "export"))
		ft_export(argc, argv, env);
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset(argc, argv, env);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(argc, argv, env);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argc, argv, env);
	else
		printf("%s is not a valid command\n", argv[0]);
}

void	start_repl(t_env *env)
{
	char		*shell;
	t_token		*tokens_lst;
	// t_ast_node	*ast_tree;

	while (true)
	{		
		shell = init_shell(env);
		if (!shell)
			continue ;
		tokens_lst = create_tokens_list(shell);
		expand_shell(tokens_lst, env);
		if (!check_errors(tokens_lst))
		{
			handle_here_docs(tokens_lst, env);
			printf("> ------- Tokens ------- <\n\n");
			print_tokens(tokens_lst);
			// ast_tree = create_ast(tokens_lst);
			// printf("\n> ------- AST ------- <\n\n");
			// print_tree(ast_tree, 0);
		}
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
	// start_repl(env);
	while (true)
	{		
		char *shell = init_shell(env);
		if (!shell)
			continue ;
		char **av = ft_split(shell, ' ');
		int ac = 0; while (av[ac]) ac++;
		run_builtin(ac, av, env);
	}
	return (0);
}
