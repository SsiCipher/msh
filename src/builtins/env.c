/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/09/11 03:15:21 by cipher           ###   ########.fr       */
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
		exit_code = print_builtin_error("env", NULL, "No such file or directory", 127);
	while (++i < env->length)
	{
		if (ft_indexof(env->content[i], '=') != -1)
			printf("%s\n", env->content[i]);
	}
	return (exit_code);
}
