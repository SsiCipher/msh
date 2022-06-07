/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:12:52 by yanab             #+#    #+#             */
/*   Updated: 2021/11/14 14:12:52 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*char_dest;
	char	*char_src;

	char_dest = (char *)dest;
	char_src = (char *)src;
	if (dest == src)
		return (dest);
	if (src > dest)
	{
		while (n--)
			*char_dest++ = *char_src++;
	}
	else
	{
		while (n--)
			*(char_dest + n) = *(char_src + n);
	}
	return (dest);
}
