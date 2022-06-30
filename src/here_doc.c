/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:06:17 by yanab             #+#    #+#             */
/*   Updated: 2022/06/30 12:55:05 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*

- [ ] empty here_doc
- [ ] join content by \n
- [ ] multiple here_docs
- [ ] variable expansion

*/

/**
 * Handle the start and read of here_docs + variable expansions
 * 
 * @param	token_list t_token struct containing the list of tokens
 * @param	env t_env struct containing all the environment variables
 */
// void	handle_here_docs(t_token *token_lst, t_env *env)
// {
// 	t_token	*tk;
// 	char	*temp;
// 	char	*line;
// 	char	*limiter;
// 	char	*here_doc_content;

// 	tk = token_lst;
// 	while (tk)
// 	{
// 		here_doc_content = NULL;
// 		if (tk->type == HERE_DOC)
// 		{
// 			limiter = tk->next->content;
// 			line = readline("heredoc> ");
// 			while (line)
// 			{
// 				if (
// 					!ft_strncmp(line, limiter, ft_strlen(limiter))
// 					&& *(line + ft_strlen(limiter)) == '\0'
// 				)
// 					break ;
// 				temp = here_doc_content;
// 				here_doc_content = ft_strjoin_many(3, here_doc_content, line, "\n");
// 				free(temp);
// 				free(line);
// 				line = readline("heredoc> ");
// 			}
// 			free(tk->next->content);
// 			if (here_doc_content)
// 				tk->next->content = expand_vars(here_doc_content, env);
// 		}
// 		tk = tk->next;
// 	}
// }

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

void	handle_here_docs(t_token *token_lst, t_env *env)
{
	t_token	*tk;
	char	*line;
	char	*temp;
	char	*limiter;

	(void)env;
	tk = token_lst;
	while (tk)
	{
		if (tk->type == HERE_DOC)
		{
			temp = tk->content;
			tk->content = ft_strdup("");
			free(temp);
			limiter = remove_quotes(tk->next->content);
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
			tk->length = ft_strlen(tk->content);
			if (!ft_strchr(tk->next->content, '"') && !ft_strchr(tk->next->content, '\''))
				tk->content = expand_vars(tk->content, env);
			delete_token(tk->next);
		}
		tk = tk->next;
	}
}
