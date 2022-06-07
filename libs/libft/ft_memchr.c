/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:12:35 by yanab             #+#    #+#             */
/*   Updated: 2022/01/24 08:06:14 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char		*cs;
	unsigned char	unc;
	size_t			i;

	cs = (const char *)s;
	unc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (cs[i] == c || cs[i] == unc)
			return ((void *)(&cs[i]));
		i++;
	}
	return (NULL);
}
