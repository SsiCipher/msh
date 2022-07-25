#include "msh.h"

/**
 * Get the type of the current token
 * 
 * @param	str the string to scan for tokens
 * @return	t_type enum value that refers to the token type
 */
t_type	tkn_type(char *str)
{
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
	else
		return (CMD);
}

/**
 * Get the length of the token
 * 
 * @param	type the type of the token
 * @return	the length of the token
 */
int	tkn_length(t_type type)
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

/**
 * Tokenize the given string
 * 
 * @param	str the string to parse
 * @return	tokens extraxted from the string
 */
t_token	*create_tokens_list(char *shell)
{
	int			i;
	int			len;
	t_token		*lst;
	bool		is_quoted;
	char		quote_type;
	t_type		curr_tkn_type;

	i = 0;
	lst = NULL;
	is_quoted = false;
	while (shell[i])
	{
		while (ft_isspace(shell[i]))
			i++;
		if (shell[i] == '\0')
			break ;
		curr_tkn_type = tkn_type(&shell[i]);
		if (curr_tkn_type != CMD && !is_quoted)
		{
			push_token(&lst, create_token(&shell[i], curr_tkn_type, tkn_length(curr_tkn_type)));
			i += tkn_length(curr_tkn_type);
		}
		else if (curr_tkn_type == CMD)
		{
			len = 0;
			is_quoted = false;
			quote_type = '\0';
			while (tkn_type(&shell[i + len]) == CMD && shell[i + len])
			{
				if (shell[i + len] == '"' || shell[i + len] == '\'')
				{
					if (quote_type == '\0')
					{
						is_quoted = true;
						quote_type = shell[i + len];
					}
					else if (quote_type == shell[i + len])
					{
						is_quoted = false;
						quote_type = '\0';
					}
				}
				if (ft_isspace(shell[i + len]) && !is_quoted)
					break ;
				else
					len++;
			}
			push_token(&lst, create_token(&shell[i], CMD, len));
			i += len;
		}
	}
	return (lst);
}
