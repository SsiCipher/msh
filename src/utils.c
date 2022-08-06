/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:37:54 by cipher            #+#    #+#             */
/*   Updated: 2022/08/04 09:39:27 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	toggle_quote(char curr_char, char *quote_type)
{
	if (curr_char == '"' || curr_char == '\'')
	{
		if (!(*quote_type))
			*quote_type = curr_char;
		else if (curr_char == *quote_type)
			*quote_type = '\0';
	}
}

/**
 * Remove quotes from a string
 * 
 * @param	str the string to remove quotes from
 * @return	a new string with quotes removed
 */
char    *unquote_text(char *str)
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
