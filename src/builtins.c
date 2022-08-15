/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/08/15 17:51:57 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

// TODO: exit code for each command
// TODO: write errors to stderr

void	print_builtin_error(char *cmd, char *pre_error, char *error)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (pre_error)
	{
		ft_putstr_fd(pre_error, STDERR_FILENO);
	    ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
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
			ft_putstr_fd(argv[i], STDOUT_FILENO);
			if (i != argc - 1)
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

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
			if (check_name(name))
				edit_var(env, name, value, append);
			else
				print_builtin_error("export", tmp, "is not a valid identifier");			
				// printf("msh: export: %s is not a valid identifier\n", tmp);
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

void	ft_exit(int argc, char **argv, t_env *env)
{
	long long	exit_code;

	(void)env;
	printf("exit\n");
	if (argc == 1)
		exit(EXIT_SUCCESS);
	else
	{
		exit_code = atoi_check(argv[1]);
		if (exit_code == -1)
		{
			print_builtin_error("exit", argv[1], "numeric argument required");
			// printf("msh: exit: %s: numeric argument required\n", argv[1]);
			exit(2);
		}
		if (argc > 2)
			print_builtin_error("exit", NULL, "too many arguments");
			// printf("msh: exit: too many arguments\n");
		else
			exit((unsigned short)exit_code);
	}
}
