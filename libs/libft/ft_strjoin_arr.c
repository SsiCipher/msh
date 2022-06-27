/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:03:16 by yanab             #+#    #+#             */
/*   Updated: 2022/06/27 06:10:05 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_arr(char **arr)
{
	int		i;
	char	*temp;
	char	*output;

	i = 0;
	output = NULL;
	while (arr[i])
	{
		if (i)
		{
			temp = output;
			output = ft_strjoin(output, " ");
			free(temp);
		}
		temp = output;
		output = ft_strjoin(output, arr[i]);
		free(temp);
		i++;
	}
	return (output);
}
