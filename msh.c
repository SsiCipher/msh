#include "msh.h"

char	*create_prompt(t_env *env)
{
	char	*prompt;

	prompt = ft_strjoin_many(
			5,
			"\e[1;32m",
			get_env_var(env, "USER"),
			" • \e[1;36m\x1B[1;34m",
			get_env_var(env, "PWD"),
			"\x1B[0m » "
			);
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

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_token	*token_lst;
	char	*shell;
	t_token	*t;

	(void)argc;
	(void)argv;
	env = copy_env(envp);
	token_lst = NULL;
	while (true)
	{
		shell = readline(create_prompt(env));
		add_history(shell);
		tokenize_shell(shell, &token_lst);

		t = token_lst;
		while (t != NULL)
		{
			if (
				(t->type == DOUBLE_QUOTE || t->type == SIMPLE_CMD)
				&& ft_memchr(t->content, '$', t->length)
			)
				t->content = expand_vars(t->content, env);
			else if (
				t->type == SIMPLE_CMD
				&& ft_memchr(t->content, '*', t->length)
			)
				t->content = expand_wildcard(t->content, "./");

			t = t->next;
		}

		if (!check_errors(token_lst))
			print_tokens(token_lst);

		free(shell);
		free_all_tokens(&token_lst);
	}
	return (0);
}

// echo "sdfsdf" > f && echo "$ddfg" > f1s && echo '$sdfsf' && echo $USER > f4
