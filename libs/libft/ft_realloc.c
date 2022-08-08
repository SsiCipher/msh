/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:18:35 by yanab             #+#    #+#             */
/*   Updated: 2022/08/08 10:26:10 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_buff;

	new_buff = (void *)malloc(new_size);
	if (!new_buff)
		return (NULL);
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr != NULL)
	{
		ft_memmove(new_buff, ptr, old_size);
		free(ptr);
	}
	return (new_buff);
}
