/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:14:05 by yanab             #+#    #+#             */
/*   Updated: 2022/01/24 08:17:11 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	src_length;
	unsigned int	dest_length;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	src_length = ft_strlen(src);
	dest_length = ft_strlen(dst);
	if (dest_length > dstsize || dstsize == 0)
		return (dstsize + src_length);
	i = 0;
	while (src[i] && dest_length + i < dstsize - 1)
	{
		dst[dest_length + i] = src[i];
		i++;
	}
	dst[dest_length + i] = '\0';
	return (dest_length + src_length);
}
