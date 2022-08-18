/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:37:54 by cipher            #+#    #+#             */
/*   Updated: 2022/08/18 09:04:10 by cipher           ###   ########.fr       */
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
	char	*output;
	char	quote_type;

	i = -1;
	j = 0;
	output = malloc(sizeof(char) * (ft_strlen(str) + 1));
	quote_type = '\0';
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '"')
			output[j++] = str[i];
		else
		{
			quote_type = str[i++];
			while (str[i] != quote_type)
				output[j++] = str[i++];
			quote_type = '\0';
		}
	}
	output[j] = '\0';
	output = ft_realloc(output, ft_strlen(output) + 1, ft_strlen(output) + 1);
	return (output);
}
