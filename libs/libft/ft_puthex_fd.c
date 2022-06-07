/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:15:27 by marvin            #+#    #+#             */
/*   Updated: 2022/01/24 08:08:57 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_fd(unsigned int n, int fd, int is_prefixed)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (is_prefixed)
		ft_putstr_fd("0x", fd);
	if (n >= 16)
		ft_puthex_fd(n / 16, fd, FALSE);
	ft_putchar_fd(base[n % 16], fd);
}
