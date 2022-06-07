/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:13:23 by yanab             #+#    #+#             */
/*   Updated: 2022/01/24 08:09:54 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_parts(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if (*str == '\0')
		return (0);
	while (str[i] == sep)
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == sep && str[i + 1] != sep && str[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	*ft_nth_part(char const *str, char sep, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if (*str == '\0')
		return (&((char *)str)[0]);
	while (str[i] == sep)
		i++;
	if (str[i] == '\0')
		return (&((char *)str)[0]);
	while (str[i])
	{
		if (count == n)
			return (&((char *)str)[i]);
		if (str[i] == sep && str[i + 1] != sep && str[i + 1] != '\0')
			count++;
		i++;
	}
	return (NULL);
}

static int	ft_partlen(char *part_start, char sep)
{
	int	len;

	len = 0;
	while (part_start[len] && part_start[len] != sep)
		len++;
	return (len);
}

static void	free_split(char **split_str, int i)
{
	while (i--)
		free(split_str[i]);
	free(split_str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	*part_start;
	int		parts_count;
	char	**split_str;

	if (s == NULL)
		return (NULL);
	parts_count = ft_count_parts(s, c);
	split_str = (char **)malloc(sizeof(char *) * (parts_count + 1));
	if (!split_str)
		return (NULL);
	i = -1;
	while (++i < parts_count)
	{
		part_start = ft_nth_part(s, c, i + 1);
		split_str[i] = ft_substr(part_start, 0, ft_partlen(part_start, c));
		if (!split_str[i])
		{
			free_split(split_str, i);
			return (NULL);
		}
	}
	split_str[i] = NULL;
	return (split_str);
}
