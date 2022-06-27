/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:06:17 by yanab             #+#    #+#             */
/*   Updated: 2022/06/27 06:07:05 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Handle the start and read of here_docs + variable expansions
 * 
 * @param	token_list t_token struct containing the list of tokens
 * @param	env t_env struct containing all the environment variables
 */
void	handle_here_docs(t_token *token_lst, t_env *env)
{
	t_token	*tk;
	char	*temp;
	char	*line;
	char	*limiter;
	char	*here_doc_content;

	tk = token_lst;
	while (tk)
	{
		here_doc_content = NULL;
		if (tk->type == HERE_DOC)
		{
			limiter = tk->next->content;
			write(STDIN_FILENO, "heredoc> ", 9);
			line = get_next_line(STDIN_FILENO);
			while (line)
			{
				write(STDIN_FILENO, "heredoc> ", 9);
				if (
					!ft_strncmp(line, limiter, ft_strlen(limiter))
					&& *(line + ft_strlen(limiter)) == '\n'
				)
					break ;
				temp = here_doc_content;
				here_doc_content = ft_strjoin(here_doc_content, line);
				free(temp);
				free(line);
				line = get_next_line(STDIN_FILENO);
			}
			free(tk->next->content);
			tk->next->content = expand_vars(here_doc_content, env);
		}
		tk = tk->next;
	}
}
