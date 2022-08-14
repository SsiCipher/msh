/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/08/14 16:42:14 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	print_builtin_error(char *cmd, char *error)
{
	printf("msh: %s: %s\n", cmd, error);
}

void	ft_echo(int argc, char **argv)
{
	int		i;
	bool	print_newline;

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
			ft_putstr_fd(argv[i], 1);
			if (i != argc - 1)
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (print_newline)
		ft_putchar_fd('\n', 1);
}

void	ft_cd_goto(char *path, t_env *env)
{
	char	*prev_wd_path;
	char	*new_wd_path;

	prev_wd_path = getcwd(NULL, 0);
	if (chdir(path))
		print_builtin_error("cd", strerror(errno));
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

	if (argc > 2)
		print_builtin_error("cd", "too many arguments");
	else if (argc == 2)
		path = argv[1];
	else
	{
		path = get_var(env, "HOME");
		if (!path)
			print_builtin_error("cd", "HOME not set");
	}
	if (path && argc <= 2)
		ft_cd_goto(path, env);
	if (path && argc == 1)
		free(path);
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

bool	parse_var(char *line, char **name, char **value)
{
	int		i;
	bool	append;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	*name = line;
	*value = line + i;
	append = (i != 0 && line[i - 1] == '+');
	if (append)
		line[i - 1] = '\0';
	if (**name == '=' || **name == '\0')
		*name = NULL;
	if (**value == '=')
		*value += 1;
	else
		*value = NULL;
	line[i] = '\0';
	return (append);
}

bool	check_name(char *name)
{
	int	i;

	i = -1;
	if (!name)
		return (false);
	while (name[++i])
	{
		if (!isalnum(name[i]) && name[i] != '_')
			return (false);
	}
	return (true);
}

void	ft_export_list(t_env *env)
{
	size_t	i;
	int		eq_i;

	i = -1;
	while (++i < env->length)
	{
		eq_i = ft_indexof(env->content[i], '=');
		if (eq_i == -1)
			printf("declare -x %s\n", env->content[i]);
		else
			printf("declare -x %.*s=\"%s\"\n", eq_i, env->content[i],
				&env->content[i][eq_i + 1]);
	}
}

void	ft_export(int argc, char **argv, t_env *env)
{
	size_t	i;
	char	*tmp;
	char	*name;
	char	*value;
	bool	append;

	if (argc == 1)
		ft_export_list(env);
	else
	{
		i = 0;
		while (++i < (size_t)argc)
		{
			tmp = ft_strdup(argv[i]);
			append = parse_var(argv[i], &name, &value);
			if (!check_name(name))
				printf("msh: export: %s is not a valid identifier\n", tmp);
			else
				edit_var(env, name, value, append);
			free(tmp);
		}
	}
}

void	ft_unset(int argc, char **argv, t_env *env)
{
	int	i;

	i = 0;
	while (++i < argc)
		delete_var(env, argv[i]);
}

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

void	ft_exit(int argc, char **argv, t_env *env)
{
	unsigned long long	exit_code;

	(void)env;
	printf("exit\n");
	if (argc == 1)
		exit(130);
	else if (argc == 2)
	{
		if (exit_code > LLONG_MAX || exit_code == -1)
		{
			printf("msh: exit: %s: numeric argument required\n", argv[1]);
			exit(2);
		}
		exit((unsigned short)exit_code);
	}
	else
	{
		
	}

	/*

	- argc == 1	=>	exit							= exit(130)
	- argc == 2	=>	exit 1; exit 255; exit 256		= exit(argv[1])
	- argc == 2	=>	exit m							= exit(2) + error
	- argc == 2	=>	exit 9223372036854775808		= exit(2) + error
	- argc > 2	=>	exit 1 2; exit 89 2342 3		= no exit + error + exit_code = 1
	- argc > 2	=>	exit 1m 3 4						= exit(2) + error
	- argc > 2	=>	exit 4 2m 23L					= no exit + error + exit_code = 1

	*/
}
