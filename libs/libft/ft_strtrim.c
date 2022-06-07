/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:14:56 by yanab             #+#    #+#             */
/*   Updated: 2021/11/14 14:14:56 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_str_contains(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static int	ft_trimstart(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_str_contains(set, str[i]))
			return (i);
		i++;
	}
	if (!ft_str_contains(set, str[i]))
		return (i);
	return (0);
}

static int	ft_trimend(char *str, char *set)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = len - 1;
	while (i >= 0)
	{
		if (!ft_str_contains(set, str[i]))
			return (i + 1);
		i--;
	}
	if (!ft_str_contains(set, str[i]))
		return (i + 1);
	return (len - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*trimmed_str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = ft_trimstart((char *)s1, (char *)set);
	end = ft_trimend((char *)s1, (char *)set);
	if (start > end)
		return (ft_strdup(""));
	trimmed_str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!trimmed_str)
		return (NULL);
	i = start;
	while (i < end)
	{
		trimmed_str[i - start] = s1[i];
		i++;
	}
	trimmed_str[i - start] = '\0';
	return (trimmed_str);
}
