/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/08/22 05:26:14 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_pwd(int argc, char **argv)
{
	char	*current_wd;

	(void)argv;
	(void)argc;
	current_wd = getcwd(NULL, 0);
	ft_putendl_fd(current_wd, 1);
	free(current_wd);
}
