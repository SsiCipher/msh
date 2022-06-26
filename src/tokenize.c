#include "msh.h"

bool	is_meta_char(t_type type)
{
	return (
		type == HERE_DOC
		|| type == REDIRECT_APPEND
		|| type == REDIRECT_IN
		|| type == REDIRECT_OUT
		|| type == AND
		|| type == OR
		|| type == PIPE
	);
}

t_token		*parse_shell(char *shell)
{
	int		i;
	t_token	*tokens;
	t_type	tk_type;
	int		cmd_len;
	int		tk_len;

	i = 0;
	tokens = NULL;
	while (shell[i])
	{
		while (ft_isspace(shell[i]))
			i++;
		if (shell[i] == '\0')
			return (NULL);
		tk_type = tkn_type(&shell[i]);
		if (tk_type != SIMPLE_CMD)
		{
			tk_len = tkn_length(tk_type);
			push_token(&tokens, create_token(&shell[i], tk_type, tk_len));
			i += tk_len;
		}
		else
		{
			cmd_len = 0;
			while (
				tkn_type(&shell[i + cmd_len]) == SIMPLE_CMD
				&& !is_meta_char(tkn_type(&shell[i + cmd_len]))
				&& shell[i + cmd_len]
			)
				cmd_len++;
			while (ft_isspace(shell[i + cmd_len - 1]))
				cmd_len--;
			push_token(&tokens, create_token(&shell[i], SIMPLE_CMD, cmd_len));
			i += cmd_len;
		}
		
	}
	return (tokens);
}
