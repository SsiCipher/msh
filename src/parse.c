#include "msh.h"

t_token_types	get_t_type(char *str)
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
	else if (!ft_strncmp(str, "&&", 2))
		return (AND);
	else if (!ft_strncmp(str, "||", 2))
		return (OR);
	else if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(str, "(", 1))
		return (OPEN_QUOTE);
	else if (!ft_strncmp(str, ")", 1))
		return (CLOSE_QUOTE);
	// else if (!ft_strncmp(str, "$", 1))
	// 	return (SIMPLE_CMD);
	// else if (!ft_strncmp(str, "*", 1))
	// 	return (ASTERISK);
	else
		return (SIMPLE_CMD);
}

int		get_t_length(t_token_types type)
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
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->content = ft_substr(content, 0, length);
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

void	free_all_tokens(t_token **tokens_lst)
{
	t_token *curr = *tokens_lst;
	while (curr != NULL)
	{
		free(curr->content);
		free(curr);
		curr = curr->next;
	}
	*tokens_lst = NULL;
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

		t_token_types t = get_t_type(str + i);
		if (t == SIMPLE_CMD)
		{
			int cmd_length = 0;
			while (
				get_t_type(str + i + cmd_length) == SIMPLE_CMD
				&& !ft_isspace(str[i + cmd_length]) && str[i + cmd_length] != '\0'
			)
				cmd_length++;
			push_token(tokens, create_token(str + i, SIMPLE_CMD, cmd_length));
			i += cmd_length;
		}
		else
		{
			int tok_len = get_t_length(t);
			int quotes_length = (t == SINGLE_QUOTE || t == DOUBLE_QUOTE);
			while (get_t_type(str + i + quotes_length) != t && str[i + quotes_length] != '\0')
				quotes_length++;
			push_token(tokens, create_token(str + i, t, tok_len + quotes_length));
			i += tok_len + quotes_length;
		}
	}
}
