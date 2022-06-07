/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:12:41 by yanab             #+#    #+#             */
/*   Updated: 2021/11/19 13:40:49 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*char_s1;
	unsigned char	*char_s2;

	i = 0;
	char_s1 = (unsigned char *)s1;
	char_s2 = (unsigned char *)s2;
	while (i < n && char_s1[i] == char_s2[i])
		i++;
	if (i < n)
		return (char_s1[i] - char_s2[i]);
	return (0);
}
