/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:10:38 by yanab             #+#    #+#             */
/*   Updated: 2021/11/14 14:10:38 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nstr)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	while (ft_isspace(nstr[i]))
		i++;
	sign = 1;
	if (nstr[i] == '-' || nstr[i] == '+')
		if (nstr[i++] == '-')
			sign *= -1;
	num = 0;
	while (nstr[i] >= '0' && nstr[i] <= '9')
		num = num * 10 + (nstr[i++] - '0');
	return (num * sign);
}
