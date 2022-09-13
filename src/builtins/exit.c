/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/09/11 03:16:01 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

long long	atoi_check(char *number)
{
	int					i;
	int					sign;
	unsigned long long	num;

	i = 0;
	if (*number == '\0' || ft_strlen(number) > 20)
		return (-1);
	sign = 1;
	if (number[i] == '-' || number[i] == '+')
	{
		if (number[i++] == '-')
			sign = -1;
	}
	num = 0;
	while (number[i])
	{
		if (number[i] < '0' || number[i] > '9')
			return (-1);
		num = num * 10 + (number[i++] - '0');
	}
	if ((sign == 1 && num > LLONG_MAX) || (sign == -1 && num - 1 > LLONG_MAX))
		return (-1);
	return (num * sign);
}

int	ft_exit(int argc, char **argv, t_env *env)
{
	long long	exit_value;
	int			exit_code;

	(void)env;
	exit_code = EXIT_SUCCESS;
	printf("exit\n");
	if (argc == 1)
		exit(EXIT_SUCCESS);
	else
	{
		exit_value = atoi_check(argv[1]);
		if (exit_value == -1)
		{
			print_builtin_error("exit", argv[1], "numeric argument required", 2);
			exit(2);
		}
		if (argc > 2)
			exit_code = print_builtin_error("exit", NULL, "too many arguments", 1);
		else
			exit((unsigned short)exit_value);
	}
	return (exit_code);
}
