/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:15:02 by yanab             #+#    #+#             */
/*   Updated: 2021/11/14 14:15:02 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sstr;
	size_t	s_len;
	int		total_alloc_size;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len - start > s_len)
		total_alloc_size = s_len + 1;
	else
		total_alloc_size = len;
	sstr = (char *)malloc(sizeof(char) * (total_alloc_size + 1));
	if (!sstr)
		return (NULL);
	i = 0;
	while (i < len && s[i] && start < s_len)
	{
		sstr[i] = s[start + i];
		i++;
	}
	sstr[i] = '\0';
	return (sstr);
}
