#include "msh.h"

t_type	tkn_type(char *str)
{
	// if (!ft_strncmp(str, "'", 1))
	// 	return (SINGLE_QUOTE);
	// else if (!ft_strncmp(str, "\"", 1))
	// 	return (DOUBLE_QUOTE);
	if (!ft_strncmp(str, "<<", 2))
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
	// else if (!ft_strncmp(str, "(", 1))
	// 	return (OPEN_QUOTE);
	// else if (!ft_strncmp(str, ")", 1))
	// 	return (CLOSE_QUOTE);
	// else if (!ft_strncmp(str, "$", 1))
	// 	return (SIMPLE_CMD);
	// else if (!ft_strncmp(str, "*", 1))
	// 	return (ASTERISK);
	else
		return (SIMPLE_CMD);
}

int		tkn_length(t_type type)
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

t_token	*create_token(char *content, t_type type, int length)
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

void	free_tokens(t_token **tokens_lst)
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
