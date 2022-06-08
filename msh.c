#include "msh.h"

t_token_types	get_type(char *str)
{
	if (!ft_strncmp(str, "'", 1))
		return (SINGLE_QUOTE);
	else if (!ft_strncmp(str, "\"", 1))
		return (DOUBLE_QUOTE);
	else if (!ft_strncmp(str, "<<", 2))
		return (HERE_DOC);
	else if (!ft_strncmp(str, ">>", 2))
		return (REDIRECT_APPEND);
	else if (!ft_strncmp(str, "<", 1))
		return (REDIRECT_IN);
	else if (!ft_strncmp(str, ">", 1))
		return (REDIRECT_OUT);
	else if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(str, "$", 1))
		return (SIMPLE_CMD);
	else if (!ft_strncmp(str, "&&", 2))
		return (AND);
	else if (!ft_strncmp(str, "||", 2))
		return (OR);
	else if (!ft_strncmp(str, "*", 1))
		return (ASTERISK);
	else
		return (SIMPLE_CMD);
}

int	get_length(t_token_types type)
{
	if (
		type == HERE_DOC
		|| type == REDIRECT_APPEND
		|| type == AND
		|| type == OR
	)
		return (2);
	return (1);
}

t_token	*create_token(char *content, t_token_types type, int length)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->content = content;
	new_token->type = type;
	new_token->length = length;
	new_token->next = NULL;
	return (new_token);
}

void	push_token(t_token **lst, t_token *new_token)
{
	t_token	*end_list;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new_token;
	else
	{
		end_list = *lst;
		while (end_list->next)
			end_list = end_list->next;
		end_list->next = new_token;
	}
}

void	free_all_tokens(t_token **token)
{
	t_token *curr = *token;
	while (curr != NULL)
	{
		free(curr);
		curr = curr->next;
	}
	*token = NULL;
}

void	tokenize_shell(char *str, t_token **tokens)
{
	int		i = 0;

	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\0')
			return ;

		t_token_types t = get_type(str + i);
		if (t == SIMPLE_CMD)
		{
			int cmd_length = 0;
			while (get_type(str + i + cmd_length) == SIMPLE_CMD && !ft_isspace(str[i + cmd_length]) && str[i + cmd_length] != '\0')
				cmd_length++;
			push_token(tokens, create_token(str + i, SIMPLE_CMD, cmd_length));
			i += cmd_length;
		}
		else
		{
			int tok_len = get_length(t);
			int quotes_length = (t == SINGLE_QUOTE || t == DOUBLE_QUOTE);
			while (get_type(str + i + quotes_length) != t && str[i + quotes_length] != '\0')
				quotes_length++;
			push_token(tokens, create_token(str + i, t, tok_len + quotes_length));
			i += tok_len + quotes_length;
		}
	}
}

char *ft_str_replace(char *str, char *find, char *replace)
{
	int find_len = ft_strlen(find);
	int str_len = ft_strlen(str);

	char *find_i = ft_strstr(str, find);
	char *start = ft_substr(str, 0, find_i - str);
	char *end = ft_substr(str, (unsigned int)(find_i - str) + find_len, str_len);
	char *output = ft_strjoin(start, replace);
	output = ft_strjoin(output, end);
	return (output);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	t_token	*token_lst;
	char	*prompt;

	env = dup_env(envp);
	token_lst = NULL;
	while (TRUE)
	{
		prompt = ft_strjoin("\x1B[1;34m", get_env_var(env, "USER"));
		prompt = ft_strjoin(prompt, " ");
		prompt = ft_strjoin(prompt, get_env_var(env, "PWD"));
		prompt = ft_strjoin(prompt, " »\x1B[0m ");
		char *shell = readline(prompt);

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
				printf("type = [%u]\n", t->type);
				write(1, "content = [", 11);
				// printf("content = [%s]\n", get_env_var(env, ft_substr(t->content, 1, t->length)));
				write(1, t->content, t->length);
				write(1, "]\n", 2);
			}
			t = t->next;
		}

		free_all_tokens(&token_lst);
		free(shell);
	}
	// printf("%s\n", ft_str_replace("hello$var asdasadsrest", "$var", "var_value_example"));
	return (0);
}

// echo "sdfsdf" > f && echo "$ddfg" > f1 && echo '$sdfsf' && echo $USER > f4
