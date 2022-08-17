/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:37:54 by cipher            #+#    #+#             */
/*   Updated: 2022/08/17 08:19:31 by cipher           ###   ########.fr       */
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

// TODO: change realloc to ft_realloc

/**
 * Remove quotes from a string
 * 
 * @param	str the string to remove quotes from
 * @return	a new string with quotes removed
 */
char	*unquote_text(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*output;
	char	quote_type;

	i = 0;
	j = 0;
	len = 0;
	output = NULL;
	quote_type = '\0';
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			output = realloc(output, sizeof(char) * (len + 1));
			output[j++] = str[i];
		}
		else
		{
			quote_type = str[i++];
			while (str[i] != quote_type)
			{
				output = realloc(output, sizeof(char) * (len + 1));
				output[j++] = str[i++];
			}
			quote_type = '\0';
		}
		i++;
	}
	output = realloc(output, sizeof(char) * (len + 1));
	output[j] = '\0';
	return (output);
}
