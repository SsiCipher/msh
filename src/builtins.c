/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/08/04 09:30:12 by cipher           ###   ########.fr       */
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

	i = 0;
	print_newline = true;
	if (argc > 1)
	{
		while (!ft_strcmp(argv[++i], "-n"))
			print_newline = false;
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
			printf("prev: %s\n", prev_wd_path);
			new_wd_path = getcwd(NULL, 0);
			edit_var(env, "OLDPWD", prev_wd_path);
			edit_var(env, "PWD", new_wd_path);
			free(new_wd_path);
		}
		free(prev_wd_path);
	}
}

void	ft_pwd(int argc, char **argv)
{
	char	*current_wd;

	(void)argv;
	if (argc > 1)
	{
		ft_putendl_fd("msh: pwd: too many arguments", 2);
		return ;
	}
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

void	ftt_export(char *new_var, t_env *env)
{
	char **new_env_content;

	new_env_content = (char **)malloc(sizeof(char *) * (env->length + 2));
	for (size_t i = 0; i < env->length; i++)
		new_env_content[i] = env->content[i];
	free(env->content);
	env->content = new_env_content;
	env->content[env->length] = ft_strdup(new_var);
	env->content[env->length + 1] = NULL;
	env->length += 1;
}

int	ft_strchr_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], str, ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}

void	ft_unset(char *variable_name, t_env *env)
{
	int		fill_i;
	char	**new_env_content;

	if (ft_strchr_array(env->content, variable_name) != -1)
	{
		fill_i = 0;
		new_env_content = (char **)malloc(sizeof(char *) * (env->length));
		for (size_t i = 0; i < env->length; i++)
		{
			if (ft_strncmp(env->content[i], variable_name, ft_strlen(variable_name)) != 0)
				new_env_content[fill_i++] = env->content[i];
			else
				free(env->content[i]);
		}
		free(env->content);
		env->content = new_env_content;
		env->length -= 1;
	}
}

void	ft_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->length)
	{
		printf("%s\n", env->content[i]);
		i++;
	}
}

void	ft_exit(int exit_code)
{
	printf("exit\n");
	exit(exit_code);
}
