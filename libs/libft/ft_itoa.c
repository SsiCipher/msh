/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:11:27 by yanab             #+#    #+#             */
/*   Updated: 2022/01/24 08:06:04 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert_int(int n, int padding)
{
	int		i;
	int		n_length;
	char	*nstr;

	n_length = ft_intlen(n);
	i = n_length - 1;
	nstr = (char *)malloc(sizeof(char) * (n_length + 1 + padding));
	if (!nstr)
		return (NULL);
	if (padding == 1)
		nstr[0] = '-';
	while (n > 0)
	{
		nstr[i + padding] = n % 10 + '0';
		i--;
		n /= 10;
	}
	nstr[n_length + padding] = '\0';
	return (nstr);
}

char	*ft_itoa(int n)
{
	char	*nstr;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n < 0)
		nstr = convert_int(-n, 1);
	else
		nstr = convert_int(n, 0);
	return (nstr);
}
