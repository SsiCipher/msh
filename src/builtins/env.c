/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/10/12 22:03:53 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_env(int argc, char **argv, t_env *env)
{
	size_t	i;
	int		exit_code;

	(void)argc;
	(void)argv;
	i = -1;
	exit_code = EXIT_SUCCESS;
	if (env->length == 0)
		exit_code = builtin_error("env", NULL,
				"No such file or directory", 127);
	while (++i < env->length)
	{
		if (ft_indexof(env->content[i], '=') != -1)
			printf("%s\n", env->content[i]);
	}
	return (exit_code);
}
