/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:14:43 by yanab             #+#    #+#             */
/*   Updated: 2021/11/14 18:28:48 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_full_word(const char *haystack, const char *needle)
{
	int	i;

	i = 0;
	while (needle[i])
	{
		if (haystack[i] != needle[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		if (
			haystack[i] == needle[0]
			&& is_full_word(&haystack[i], needle)
		)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
