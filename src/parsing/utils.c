/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:37:54 by cipher            #+#    #+#             */
/*   Updated: 2022/08/28 22:38:10 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Toggle the quote state based on the character
 * 
 * @param	c the current character
 * @param	quote_type the quote type [', ", \0]
 * @param	is_quoted a boolean reflecting the state
 */
void	toggle_quote(char c, char *quote_type, bool *is_quoted)
{
	if (c == '\"' || c == '\'')
	{
		if (!(*quote_type))
		{
			if (is_quoted)
				*is_quoted = true;
			*quote_type = c;
		}
		else if (c == *quote_type)
		{
			if (is_quoted)
				*is_quoted = false;
			*quote_type = '\0';
		}
	}
}

void	extract_quoted(char *str, char *output, bool escape_wildcard)
{
	int		i;
	int		j;
	char	quote_type;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote_type = str[i++];
			while (str[i] != quote_type)
			{
				if (str[i] == '*' && escape_wildcard)
					output[j++] = '\\';
				output[j++] = str[i++];
			}
			quote_type = '\0';
			continue ;
		}
		output[j++] = str[i];
	}
	output[j] = '\0';
}

/**
 * Remove quotes from a string
 * 
 * @param	str the string to remove quotes from
 * @return	a new string with quotes removed
 */
char	*unquote_text(char *str, bool escape_wildcard)
{
	char	*output;

	output = malloc(sizeof(char) * (ft_strlen(str) + 1));
	extract_quoted(str, output, escape_wildcard);
	output = ft_realloc(output, ft_strlen(output) + 1, ft_strlen(output) + 1);
	return (output);
}
