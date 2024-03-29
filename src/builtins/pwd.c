/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/09/13 10:58:52 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_pwd(int argc, char **argv, t_env *env)
{
	char	*current_wd;

	(void)argv;
	(void)argc;
	(void)env;
	current_wd = getcwd(NULL, 0);
	ft_putendl_fd(current_wd, 1);
	free(current_wd);
	return (EXIT_SUCCESS);
}
