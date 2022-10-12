/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_indexof.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:51:43 by cipher            #+#    #+#             */
/*   Updated: 2022/10/12 22:03:05 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arr_indexof(char **arr, char *target)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (!ft_strcmp(arr[i], target))
			return (i);
	}
	return (-1);
}
