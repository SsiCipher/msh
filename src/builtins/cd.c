/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/10/12 22:02:47 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_cd_goto(char *path, t_env *env)
{
	char	*prev_wd_path;
	char	*new_wd_path;
	int		exit_code;

	exit_code = 0;
	prev_wd_path = getcwd(NULL, 0);
	if (chdir(path))
		exit_code = builtin_error("cd", NULL, strerror(errno), 1);
	else
	{
		new_wd_path = getcwd(NULL, 0);
		edit_var(env, "OLDPWD", prev_wd_path, false);
		edit_var(env, "PWD", new_wd_path, false);
		free(new_wd_path);
	}
	free(prev_wd_path);
	return (exit_code);
}

int	ft_cd(int argc, char **argv, t_env *env)
{
	char	*path;
	int		exit_code;

	path = NULL;
	if (argc > 2)
		exit_code = builtin_error("cd", NULL, "too many arguments", 1);
	else if (argc == 2)
		path = argv[1];
	else
	{
		path = get_var(env, "HOME");
		if (!path)
			exit_code = builtin_error("cd", NULL, "HOME not set", 1);
	}
	if (path && argc <= 2)
		exit_code = ft_cd_goto(path, env);
	if (path && argc == 1)
		free(path);
	return (exit_code);
}
