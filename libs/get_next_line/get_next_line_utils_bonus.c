/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:27:47 by yanab             #+#    #+#             */
/*   Updated: 2021/12/03 21:34:57 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	has_nl(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (*(str++) == '\n')
			return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	if (*str == '\0')
		return (0);
	return (1 + ft_strlen(str + 1));
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*char_dest;
	char		*char_src;

	i = 0;
	if (!dest && !src)
		return (NULL);
	char_dest = (char *)dest;
	char_src = (char *)src;
	while (i < n)
	{
		char_dest[i] = char_src[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		s_len;
	char	*dupicate;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	dupicate = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!dupicate)
		return (NULL);
	ft_memcpy(dupicate, s, s_len);
	dupicate[s_len] = '\0';
	return (dupicate);
}

char	*join_strs(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*joined_str;

	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	joined_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!joined_str)
		return (NULL);
	ft_memcpy(joined_str, s1, s1_len);
	ft_memcpy(joined_str + s1_len, s2, s2_len);
	joined_str[s1_len + s2_len] = '\0';
	return (joined_str);
}
