/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:13:14 by yanab             #+#    #+#             */
/*   Updated: 2022/01/24 08:08:33 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	num;

	if (n < 0)
	{
		if (n == -2147483648)
			ft_putstr_fd("-2147483648", fd);
		else
		{
			ft_putchar_fd('-', fd);
			ft_putnbr_fd(n * -1, fd);
		}
	}
	else
	{
		if (n >= 10)
			ft_putnbr_fd(n / 10, fd);
		num = n % 10 + '0';
		ft_putchar_fd(num, fd);
	}
}
