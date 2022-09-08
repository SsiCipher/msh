/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/09/08 04:52:02 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_echo(int argc, char **argv)
{
	int		i;
	bool	print_newline;

	(void)argv;
	i = 1;
	print_newline = true;
	if (argc > 1)
	{
		while (argv[i][0] == '-' && ft_every_char(&argv[i][1], 'n'))
		{
			print_newline = false;
			i++;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], STDOUT_FILENO);
			if (i != argc - 1)
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
