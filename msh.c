/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:11:27 by yanab             #+#    #+#             */
/*   Updated: 2022/06/30 12:44:39 by yanab            ###   ########.fr       */
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
	if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	if (type == HERE_DOC)
		return ("HERE_DOC");
	if (type == REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == PIPE)
		return ("PIPE");
	if (type == OPEN_QUOTE)
		return ("OPEN_QUOTE");
	if (type == CLOSE_QUOTE)
		return ("CLOSE_QUOTE");
	else
		return ("SIMPLE_CMD");
}

void	print_tokens(t_token *tokens_lst)
{
	t_token	*curr_tk;

	curr_tk = tokens_lst;
	while (curr_tk)
	{
		printf("content[%d] = [%s]\t\t\t{%s}\n", curr_tk->length, curr_tk->content, get_type_name(curr_tk->type));
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
		token_lst = parse_shell(shell);
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
