/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/08/22 05:23:46 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_env(int argc, char **argv, t_env *env)
{
	size_t	i;

	(void)argc;
	(void)argv;
	i = -1;
	while (++i < env->length)
	{
		if (ft_indexof(env->content[i], '=') != -1)
			printf("%s\n", env->content[i]);
	}
}
