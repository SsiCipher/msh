#include "msh.h"

char	*create_prompt(t_env *env)
{
	char	*prompt;
	char	*user;
	char	*cwd;

	user = get_env_var(env, "USER");
	if (!user)
		user = ft_strdup("USER");
	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin_many(
			5,
			"\e[1;32m", user, " • \e[1;36m\x1B[1;34m", cwd, "\x1B[0m » "
			);
	free(user);
	free(cwd);
	return (prompt);
}

void	print_tokens(t_token *first_tk)
{
	t_token *curr_tk = first_tk;

	while (curr_tk)
	{
		printf("type = [%u]\ncontent = [%s]\n", curr_tk->type, curr_tk->content);
		curr_tk = curr_tk->next;
	}
}

void	handle_expansions(t_token *token_lst, t_env *env)
{
	t_token	*t;
	char	*tmp;

	t = token_lst;
	while (t != NULL)
	{
		if (
			(t->type == DOUBLE_QUOTE || t->type == SIMPLE_CMD)
			&& ft_memchr(t->content, '$', t->length)
		)
		{
			tmp = t->content;
			t->content = expand_vars(t->content, env);
			free(tmp);
		}
		else if (
			t->type == SIMPLE_CMD
			&& ft_memchr(t->content, '*', t->length)
		)
		{
			tmp = t->content;
			t->content = expand_wildcard(t->content, "./");
			free(tmp);
		}
		t = t->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_token	*token_lst;
	char	*shell;
	char	*prompt;

	(void)argc;
	(void)argv;
	env = copy_env(envp);
	token_lst = NULL;
	while (true)
	{
		prompt = create_prompt(env);
		shell = readline(prompt);
		add_history(shell);
		tokenize_shell(shell, &token_lst);

		handle_expansions(token_lst, env);

		if (!check_errors(token_lst))
			print_tokens(token_lst);

		free(shell);
		free(prompt);
		free_all_tokens(&token_lst);
	}
	return (0);
}
