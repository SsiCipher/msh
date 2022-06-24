#include "msh.h"

/**
 * Handle the start and read of here_docs + variable expansions
 * 
 * @param token_list t_token struct containing the list of tokens
 * @param env t_env struct containing all the environment variables
 */
void	handle_here_docs(t_token *token_lst, t_env *env)
{
	t_token *tk;
	char	*limiter;
	char	*here_doc_content;

	(void)env;
	tk = token_lst;
	while (tk)
	{
		here_doc_content = NULL;
		if (tk->type == HERE_DOC)
		{
			limiter = tk->next->content;
			char *line = get_next_line(STDIN_FILENO);
			while (line)
			{
				if (
					!ft_strncmp(line, limiter, ft_strlen(limiter))
					&& *(line + ft_strlen(limiter)) == '\n'
				)
					break ;
				here_doc_content = ft_strjoin(here_doc_content, line);
				line = get_next_line(STDIN_FILENO);
			}
			free(limiter);
			tk->next->content = here_doc_content;
		}

		tk = tk->next;
	}
}
