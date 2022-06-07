#include "msh.h"

typedef enum e_token_types {
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HERE_DOC,
	REDIRECT_APPEND,
	PIPE,
	DOLLAR_SIGN,
	AND,
	OR,
	ASTERISK,
	SIMPLE_CMD
}	t_token_types;

typedef struct s_token
{
	char			*content;
	t_token_types	type;
	int				length;
	struct s_token	*next;
}	t_token;

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
		return (DOLLAR_SIGN);
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

void	ft_add_token(t_token **lst, t_token *new_token)
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

void	free_tokens(t_token **token)
{
	t_token *curr = *token;
	while (curr != NULL)
	{
		free(curr);
		curr = curr->next;
	}
	*token = NULL;
}

void	tokenize(char *str, t_token **tokens)
{
	int i = 0;
	while (str[i])
	{
		t_token	*tok;
		while (ft_isspace(*(str + i)))
			i++;
		t_token_types t = get_type(str + i);

		if (t != SIMPLE_CMD)
		{
			int tok_len = get_length(t);
			int j = 1;
			if (t == SINGLE_QUOTE || t == DOUBLE_QUOTE)
			{
				while (get_type(str + i + j) != t && str[i + j] != '\0')
					j++;
			}
			tok = create_token(str + i, t, tok_len + j);
			ft_add_token(tokens, tok);
			i += tok_len + j;
		}
		else
		{
			int j = 0;
			while (get_type(str + i + j) == SIMPLE_CMD && str[i + j] != '\0')
				j++;
			tok = create_token(str + i, SIMPLE_CMD, j);
			ft_add_token(tokens, tok);
			i += j;
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_token *token_lst = NULL;

	t_env *env;

	env = dup_env(envp);
	while (TRUE)
	{
		char *prompt = ft_strjoin("\x1B[1;34m", get_env_var(env, "USER"));
		prompt = ft_strjoin(prompt, " ");
		prompt = ft_strjoin(prompt, get_env_var(env, "PWD"));
		prompt = ft_strjoin(prompt, " »\x1B[0m ");
		char *shell = readline(prompt);
		add_history(shell);

		tokenize(shell, &token_lst);

		t_token *t = token_lst;
		while (t != NULL)
		{
			printf("type = [%u]\n", t->type);
			write(1, t->content, t->length);
			printf("\n");
			t = t->next;
		}

		free_tokens(&token_lst);
	}
	return (0);
}
