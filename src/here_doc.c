/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:06:17 by yanab             #+#    #+#             */
/*   Updated: 2022/07/30 13:45:52 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Remove all quotes from a string 
 * 
 * @param	limiter the limiter string to remove quotes from
 * @return	a new string with quotes removed
 */
char	*remove_quotes(char *limiter)
{
	int		i;
	int		j;
	int		len;
	char	*unquoted_limiter;

	i = -1;
	len = 0;
	while (limiter[++i])
		len += (limiter[i] != '"' && limiter[i] != '\'');
	unquoted_limiter = (char *)malloc(sizeof(char) * (len + 1));
	i = -1;
	j = 0;
	while (limiter[++i])
	{
		if (limiter[i] != '"' && limiter[i] != '\'')
			unquoted_limiter[j++] = limiter[i];
	}
	unquoted_limiter[j] = '\0';
	return (unquoted_limiter);
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
	char	*temp;
	char	*limiter;

	tk = token_lst;
	while (tk)
	{
		if (tk->type == HERE_DOC)
		{
			temp = tk->content;
			tk->content = ft_strdup("");
			free(temp);
			limiter = unquote_text(tk->next->content);
			line = readline("> ");
			while (line)
			{
				if (
					!ft_strncmp(line, limiter, ft_strlen(limiter))
					&& *(line + ft_strlen(limiter)) == '\0'
				)
					break ;
				temp = tk->content;
				tk->content = ft_strjoin_many(3, tk->content, line, "\n");
				free(temp);
				free(line);
				line = readline("> ");
			}
			free(line);
			free(limiter);
			if (!ft_strchr(tk->next->content, '"') && !ft_strchr(tk->next->content, '\''))
				tk->content = expand_vars(tk->content, env);
			tk->length = ft_strlen(tk->content);
			delete_token(tk->next);
		}
		tk = tk->next;
	}
}
