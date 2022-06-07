/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:14:43 by yanab             #+#    #+#             */
/*   Updated: 2022/01/24 08:20:41 by cipher           ###   ########.fr       */
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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (
			haystack[i] == needle[0]
			&& is_full_word(&haystack[i], needle)
			&& i + needle_len - 1 < len
		)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
