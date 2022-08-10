/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/08/10 06:11:02 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	print_builtin_error(char *cmd, char *error)
{
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

int is_n(char c)
{
	return (c == 'n');
}

void	ft_echo(int argc, char **argv)
{
	int i;
	bool print_newline;

	i = 1;
	print_newline = true;
	if (argc > 1)
	{
		while (argv[i][0] == '-' && ft_every(&argv[i][1], is_n))
		{
			print_newline = false;
			i++;	
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (i != argc - 1)
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (print_newline)
		ft_putchar_fd('\n', 1);
}

void	ft_cd(int argc, char **argv, t_env *env)
{
	char	*path;
	char	*prev_wd_path;
	char	*new_wd_path;

	if (argc == 2)
		path = argv[1];
	else if (argc > 2)
		print_builtin_error("cd", "too many arguments");
	else
	{
		path = get_var(env, "HOME");
		if (!path)
			print_builtin_error("cd", "HOME not set");
	}
	if (path && argc <= 2)
	{
		prev_wd_path = getcwd(NULL, 0);
		if(chdir(path))
			print_builtin_error("cd", strerror(errno));
		else
		{
			new_wd_path = getcwd(NULL, 0);
			edit_var(env, "OLDPWD", prev_wd_path, true);
			edit_var(env, "PWD", new_wd_path, true);
			free(new_wd_path);
		}
		free(prev_wd_path);
	}
}

void	ft_pwd(int argc, char **argv)
{
	char	*current_wd;

	(void)argv;
	(void)argc;
	current_wd = getcwd(NULL, 0);
	ft_putendl_fd(current_wd, 1);
	free(current_wd);
}

void	ft_export(int argc, char **argv, t_env *env)
{
	(void)argc;
	(void)argv;
	(void)env;
}

void	ft_unset(int argc, char **argv, t_env *env)
{
	(void)argc;
	(void)argv;
	(void)env;
}

void	ft_env(int argc, char **argv, t_env *env)
{
	size_t	i;

	(void)argc;
	(void)argv;
	i = -1;
	while (++i < env->length)
		printf("%s\n", env->content[i]);
}

void	ft_exit(int argc, char **argv, t_env *env)
{
	(void)argc;
	(void)argv;
	(void)env;
}
