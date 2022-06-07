/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 12:17:41 by marvin            #+#    #+#             */
/*   Updated: 2022/02/05 20:53:41 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bsort(int len, int *arr, int (*cmp)(int, int))
{
	int	i;
	int	j;
	int	is_swapped;

	i = 0;
	is_swapped = 0;
	while (i < len)
	{
		j = i;
		while (j < len)
		{
			if (cmp(arr[i], arr[j]) > 0)
			{
				ft_swap(arr, i, j);
				is_swapped = 1;
			}
			j++;
		}
		if (!is_swapped)
			break ;
		i++;
	}
}
