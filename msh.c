#include "msh.h"
#include <stdarg.h>

char *custom_join(int strs_count, ...)
{
	va_list ap;
	char *output = NULL;
	int total_len = 0;

	va_start(ap, strs_count);
	for (int i = 0; i < strs_count; i++)
		total_len += ft_strlen(va_arg(ap, char *));
	va_end(ap);
	output = (char *)ft_calloc(total_len + 1, sizeof(char));
	va_start(ap, strs_count);
	for (int i = 0; i < strs_count; i++)
		ft_strlcat(output, va_arg(ap, char *), total_len + 1);
	va_end(ap);
	return (output);
}

char	*create_prompt(t_env *env)
{
	char	*prompt;
	char	*temp;

	prompt = ft_strjoin("\e[1;32m", get_env_var(env, "USER"));
	temp = prompt;
	prompt = ft_strjoin(prompt, " • \e[1;36m\x1B[1;34m");
	free(temp);
	temp = prompt;
	prompt = ft_strjoin(prompt, get_env_var(env, "PWD"));
	free(temp);
	temp = prompt;
	prompt = ft_strjoin(prompt, "\x1B[0m » ");
	free(temp);
	return (prompt);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	t_token	*token_lst;

	env = copy_env(envp);
	token_lst = NULL;
	while (true)
	{
		char *shell = readline(create_prompt(env));

		add_history(shell);

		tokenize_shell(shell, &token_lst);

		t_token	*t = token_lst;
		while (t != NULL)
		{
			if (
				(t->type == DOUBLE_QUOTE || t->type == SIMPLE_CMD)
				&& ft_memchr(t->content, '$', t->length)
			)
			{
				t->content = preprocess_vars(t->content, env);
				printf("type = [%u]\ncontent = [%s]\n", t->type, t->content);
			}
			else if (t->type == SIMPLE_CMD && ft_memchr(t->content, '*', t->length))
			{
				int i = -1;
				t_dir *dir = read_dir_content("./");
				char *output = NULL;
				while (dir->content[++i])
				{
					if (match_wildcard(t->content, dir->content[i]))
					{
						char *temp = output;
						if (!output)
							output = custom_join(1, dir->content[i]);
						else
							output = custom_join(3, output, " ", dir->content[i]);
						free(temp);
					}
				}
				printf("type = [%u]\ncontent = [%s]\n", t->type, output);
			}
			else
				printf("type = [%u]\ncontent = [%s]\n", t->type, t->content);
			t = t->next;
		}

		free_all_tokens(&token_lst);
		free(shell);
	}

	return (0);
}

// echo "sdfsdf" > f && echo "$ddfg" > f1s && echo '$sdfsf' && echo $USER > f4
