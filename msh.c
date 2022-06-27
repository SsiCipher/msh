/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:11:27 by yanab             #+#    #+#             */
/*   Updated: 2022/06/27 06:14:56 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*create_prompt(t_env *env)
{
	char	*prompt;
	char	*user;
	char	*cwd;

	user = get_env_var(env, "USER");
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

void	print_tokens(t_token *tokens_lst)
{
	t_token	*curr_tk;

	curr_tk = tokens_lst;
	while (curr_tk)
	{
		printf("type = [%u]\ncontent = [%s]\n", curr_tk->type, curr_tk->content);
		curr_tk = curr_tk->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*shell;
	char	*prompt;
	t_token	*token_lst;

	(void)argc;
	(void)argv;
	env = copy_env(envp);
	while (true)
	{
		prompt = create_prompt(env);
		shell = readline(prompt);
		add_history(shell);
		token_lst = parse_shell(shell);
		expand_shell(token_lst, env);
		if (!check_errors(token_lst))
		{
			handle_here_docs(token_lst, env);
			print_tokens(token_lst);
		}
		free(prompt);
		free(shell);
		free_tokens(&token_lst);
	}
	return (0);
}
