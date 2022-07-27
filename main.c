/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:11:27 by yanab             #+#    #+#             */
/*   Updated: 2022/07/24 18:33:00 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*create_prompt_str(t_env *env)
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

char	*init_shell(t_env *env)
{
	char *prompt;
	char *shell;

	prompt = create_prompt_str(env);
	shell = readline(prompt);
	free(prompt);
	if (!shell)
		exit(1);
	add_history(shell);
	return (shell);
}

char *get_type_name(t_type type)
{
	if (type == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	else if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (type == HERE_DOC)
		return ("R_HEREDOC");
	else if (type == REDIRECT_APPEND)
		return ("APPEND_R");
	else if (type == REDIRECT_IN)
		return ("IN_R");
	else if (type == REDIRECT_OUT)
		return ("OUT_R");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else if (type == PIPE)
		return ("PIPE");
	else
		return ("CMD");
}

void	print_tokens(t_token *tokens_lst)
{
	t_token	*curr_tk;

	curr_tk = tokens_lst;
	while (curr_tk)
	{
		printf("%s[%d] =\t[%s]\n", get_type_name(curr_tk->type), curr_tk->length, curr_tk->content);
		curr_tk = curr_tk->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*shell;
	t_token	*token_lst;

	(void)argc;
	(void)argv;
	env = copy_env(envp);
	while (true)
	{
		shell = init_shell(env);
		token_lst = create_tokens_list(shell);
		expand_shell(token_lst, env);
		if (!check_errors(token_lst))
		{
			handle_here_docs(token_lst, env);
			print_tokens(token_lst);
		}
		free(shell);
		free_tokens(&token_lst);
	}
	return (0);
}
