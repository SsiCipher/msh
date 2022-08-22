/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/08/22 05:28:57 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_cd_goto(char *path, t_env *env)
{
	char	*prev_wd_path;
	char	*new_wd_path;

	prev_wd_path = getcwd(NULL, 0);
	if (chdir(path))
		print_builtin_error("cd", NULL, strerror(errno));
	else
	{
		new_wd_path = getcwd(NULL, 0);
		edit_var(env, "OLDPWD", prev_wd_path, false);
		edit_var(env, "PWD", new_wd_path, false);
		free(new_wd_path);
	}
	free(prev_wd_path);
}

void	ft_cd(int argc, char **argv, t_env *env)
{
	char	*path;

	path = NULL;
	if (argc > 2)
		print_builtin_error("cd", NULL, "too many arguments");
	else if (argc == 2)
		path = argv[1];
	else
	{
		path = get_var(env, "HOME");
		if (!path)
			print_builtin_error("cd", NULL, "HOME not set");
	}
	if (path && argc <= 2)
		ft_cd_goto(path, env);
	if (path && argc == 1)
		free(path);
}
