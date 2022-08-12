/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/08/12 15:26:18 by cipher           ###   ########.fr       */
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

void	ft_echo(int argc, char **argv)
{
	int i;
	bool print_newline;

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

bool	parse_var(char *line, char **name, char **value)
{
	int		i;
	bool	append;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	*name = line;
	*value = line + i;
	if (**name == '=' || **name == '\0')
		*name = NULL;
	if (**value == '=')
		*value += 1;
	else
		*value = NULL;
	line[i] = '\0';
	append = i != 0 && line[i-1] == '+';
	if (append)
		line[i-1] = '\0';
	return (append);
}

bool    check_name(char *name)
{
	int i;

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
			printf("declare -x %.*s=\"%s\"\n", eq_i, env->content[i], &env->content[i][eq_i + 1]);
	}
}

// Fix error : show the giver argv before the change
void	ft_export(int argc, char **argv, t_env *env)
{
	size_t	i;
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
			append = parse_var(argv[i], &name, &value);
			if (!check_name(name))
			{
				// for (int j = 0; argv[i][j]; j++);
				// if (argv[i][j+1] == '\0')
				print_builtin_error("export", "not a valid identifier");
			}
			else
				edit_var(env, name, value, append);
		}
	}
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
	{
		if (ft_indexof(env->content[i], '=') != -1)
			printf("%s\n", env->content[i]);
	}
}

void	ft_exit(int argc, char **argv, t_env *env)
{
	(void)argc;
	(void)argv;
	(void)env;
}
