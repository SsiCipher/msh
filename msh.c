#include "msh.h"

void	print_tokens(t_token *first_tk)
{
	t_token *curr_tk = first_tk;

	while (curr_tk)
	{
		printf("type = [%u]\ncontent = [%s]\n", curr_tk->type, curr_tk->content);
		curr_tk = curr_tk->next;
	}
}

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

char	*ft_strjoin_arr(char **arr)
{
	int i;
	char *temp;
	char *output;

	i = 0;
	output = NULL;
	while (arr[i])
	{
		if (i)
		{
			temp = output;
			output = ft_strjoin(output, " ");
			free(temp);
		}
		temp = output;
		output = ft_strjoin(output, arr[i]);
		free(temp);
		i++;
	}
	return (output);
}

void	expand_shell(t_token *token_lst, t_env *env)
{
	t_token	*t;
	char	*tmp;
	char	**cmd;

	(void)env;
	t = token_lst;
	while (t)
	{
		if (t->type == SIMPLE_CMD)
		{
			int i = -1;
			cmd = ft_split(t->content, ' ');
			while (cmd[++i])
			{
				if (ft_memchr(cmd[i], '$', t->length))
				{
					tmp = cmd[i];
					cmd[i] = expand_vars(cmd[i], env);
					free(tmp);
				}
				else if (ft_memchr(cmd[i], '*', t->length))
				{
					tmp = cmd[i];
					cmd[i] = expand_wildcard(cmd[i], "./");
					free(tmp);
				}
			}
			tmp = t->content;
			t->content = ft_strjoin_arr(cmd);
			free(tmp);
		}
		t = t->next;
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
	token_lst = NULL;
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

		free(shell);
		free(prompt);
		free_tokens(&token_lst);
	}
	return (0);
}
