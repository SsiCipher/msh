/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:06:17 by yanab             #+#    #+#             */
/*   Updated: 2022/08/16 05:45:05 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

// TODO: variable expansion in file
// TODO: random filename

bool	process_line(char *line, char *limiter, int heredoc_fd)
{
	
	if (
		!ft_strncmp(line, limiter, ft_strlen(limiter))
		&& *(line + ft_strlen(limiter)) == '\0'
	)
		return (false);
	write(heredoc_fd, line, ft_strlen(line));
	write(heredoc_fd, "\n", 1);
	free(line);
	return (true);
}

/**
 * Handle the start and read of here_docs + variable expansions
 * 
 * @param	token_list t_token struct containing the list of tokens
 * @param	env t_env struct containing all the environment variables
 */
void	handle_here_docs(t_token *token_lst, t_env *env)
{
	t_token	*tk;
	char	*line;
	char	*limiter;
	int		heredoc_fd;

	tk = token_lst;
	while (tk)
	{
		if (tk->type == R_HEREDOC)
		{
			heredoc_fd = open("/tmp/.here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (heredoc_fd == -1)
				perror("Cannot open /tmp/.here_doc");
			limiter = unquote_text(tk->next->content);
			line = readline("> ");
			while (line)
			{
				// if (
				// 	!ft_strncmp(line, limiter, ft_strlen(limiter))
				// 	&& *(line + ft_strlen(limiter)) == '\0'
				// )
				// 	break ;
				// write(heredoc_fd, line, ft_strlen(line));
				// write(heredoc_fd, "\n", 1);
				// free(line);
				if (!process_line(line, limiter, heredoc_fd))
					break ;
				line = readline("> ");
			}
			free(line);
			free(limiter);
			if (!ft_strchr(tk->next->content, '\"') && !ft_strchr(tk->next->content, '\''))
				tk->content = expand_vars(tk->content, env);
			free(tk->next->content);
			tk->next->content = ft_strdup("/tmp/.here_doc");
			tk->next->length = 14;
			close(heredoc_fd);
		}
		tk = tk->next;
	}
}
