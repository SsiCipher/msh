/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 05:28:31 by yanab             #+#    #+#             */
/*   Updated: 2022/08/17 08:11:18 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_str(char **arr, int i, int j)
{
	char	*temp;

	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int	ft_sort_str(char **array, int size, int (*cmp)(const char *, const char *))
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++j < size)
	{
		if (cmp(array[j], array[size - 1]) <= 0)
			ft_swap_str(array, i++, j);
	}
	if (i == 0)
		return (0);
	return (i - 1);
}

void	ft_qsort_str(char **array, int size,
	int (*cmp)(const char *, const char *))
{
	int	pivot_i;

	if (size > 1)
	{
		pivot_i = ft_sort_str(array, size, cmp);
		ft_qsort_str(array, pivot_i, cmp);
		ft_qsort_str(array + pivot_i + 1, size - (pivot_i + 1), cmp);
	}
}
