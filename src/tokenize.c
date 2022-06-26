#include "msh.h"

bool	is_meta_char(t_token_types type)
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

	i = 0;
	tokens = NULL;
	while (shell[i])
	{
		while (ft_isspace(shell[i]))
			i++;
		if (shell[i] == '\0')
			return (NULL);

		t_token_types tk_type = get_t_type(&shell[i]);
		if (tk_type == SIMPLE_CMD)
		{
			int cmd_len = 0;
			while (
				get_t_type(&shell[i + cmd_len]) == SIMPLE_CMD
				&& !is_meta_char(get_t_type(&shell[i + cmd_len]))
				&& shell[i + cmd_len]
			)
				cmd_len++;
			int spaces = 0;
			while (ft_isspace(shell[i + cmd_len - spaces - 1]))
				spaces++;
			push_token(&tokens, create_token(&shell[i], SIMPLE_CMD, cmd_len - spaces));
			i += cmd_len;
		}
		else
		{
			int tk_len = get_t_length(tk_type);
			push_token(&tokens, create_token(&shell[i], tk_type, tk_len));
			i += tk_len;
		}
	}
	return (tokens);
}
