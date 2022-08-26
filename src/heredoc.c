/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:06:17 by yanab             #+#    #+#             */
/*   Updated: 2022/08/25 18:55:17 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Open the heredoc file based on $SHLVL variable
 * 
 * @param	env t_env struct containing all the environment variables
 * @param	file_path a variable to set to the heredoc file path
 */
int	open_heredoc_file(t_env *env, char **file_path)
{
	int		fd;
	char	*shlvl;

	fd = -1;
	*file_path = NULL;
	shlvl = get_var(env, "SHLVL");
	if (shlvl)
	{
		*file_path = ft_strjoin("/tmp/.heredoc_", shlvl);
		fd = open(*file_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	free(shlvl);
	return (fd);
}

/**
 * Handle the start and read of here_docs + variable expansions
 * 
 * @param	limter the limiter to stop the heredoc read
 * @param	is_limiter_quoted true if the limiter is quoted, false otherwise
 * @param	env t_env struct containing all the environment variables
 */
char	*start_heredoc(char *limiter, bool is_limiter_quoted, t_env *env)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	*file_path;

	fd = open_heredoc_file(env, &file_path);
	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& *(line + ft_strlen(limiter)) == '\0')
			break ;
		tmp = line;
		if (!is_limiter_quoted)
			line = expand_vars(line, true, env);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		free(tmp);
		line = readline("> ");
	}
	free(line);
	close(fd);
	return (file_path);
}

/**
 * Handle the start and read of here_docs + variable expansions
 * 
 * @param	tkn t_token struct containing the list of tokens
 * @param	env t_env struct containing all the environment variables
 */
void	handle_heredocs(t_token *tkn, t_env *env)
{
	char	*limiter;
	char	*file_path;
	bool	is_limiter_quoted;

	while (tkn)
	{
		if (tkn->type == R_HEREDOC)
		{
			is_limiter_quoted = (ft_strchr(tkn->next->content, '\"')
					|| ft_strchr(tkn->next->content, '\''));
			limiter = unquote_text(tkn->next->content);
			file_path = start_heredoc(limiter, is_limiter_quoted, env);
			free(limiter);
			free(tkn->next->content);
			tkn->next->content = file_path;
			tkn->next->length = ft_strlen(file_path);
		}
		tkn = tkn->next;
	}
}
