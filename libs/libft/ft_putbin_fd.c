/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbin_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:16:40 by marvin            #+#    #+#             */
/*   Updated: 2022/01/24 08:09:16 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbin_fd(unsigned int n, int fd, int is_prefixed)
{
	char	*base;

	base = "01";
	if (is_prefixed)
		ft_putstr_fd("0b", fd);
	if (n >= 2)
		ft_putbin_fd(n / 2, fd, FALSE);
	ft_putchar_fd(base[n % 2], fd);
}
