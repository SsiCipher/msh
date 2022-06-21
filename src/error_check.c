#include "msh.h"

/**
 * Check tokens for syntax errors
 * 
 * @param	token_lst the list of tokens
 * @return	true if any errors were found false otherwise
 */
bool	check_errors(t_token *token_lst)
{
	t_token	*tk = token_lst;

	while (tk)
	{
		if (
			(tk->type == REDIRECT_IN || tk->type == REDIRECT_OUT || tk->type == REDIRECT_APPEND)
			&& (tk->next == NULL || tk->next->type != SIMPLE_CMD)
		)
		{
			printf("msh: syntax error: expected a file after %s\n", tk->content);
			return (true);
		}
		else if (
			(tk->type == PIPE || tk->type == AND || tk->type == OR) 
			&& (tk->next == NULL || tk->next->type != SIMPLE_CMD)
		)
		{
			printf("msh: syntax error: expected a command after %s\n", tk->content);
			return (true);
		}
		tk = tk->next;
	}
	return (false);
}
