#include "msh.c"

void	handle_expansions(t_token *token_lst, t_env *env)
{
	t_token	*t;
	char	*tmp;

	t = token_lst;
	while (t)
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

void	tokenize_shell(char *str, t_token **tokens)
{
	int		i = 0;

	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\0')
			return ;

		t_type t = tkn_type(str + i);
		if (t == SIMPLE_CMD)
		{
			int cmd_length = 0;
			while (
				tkn_type(str + i + cmd_length) == SIMPLE_CMD
				&& !ft_isspace(str[i + cmd_length]) && str[i + cmd_length] != '\0'
			)
				cmd_length++;
			push_token(tokens, create_token(str + i, SIMPLE_CMD, cmd_length));
			i += cmd_length;
		}
		else
		{
			int tok_len = tkn_length(t);
			int quotes_length = (t == SINGLE_QUOTE || t == DOUBLE_QUOTE);
			while (tkn_type(str + i + quotes_length) != t && str[i + quotes_length] != '\0')
				quotes_length++;
			push_token(tokens, create_token(str + i, t, tok_len + quotes_length));
			i += tok_len + quotes_length;
		}
	}
}
