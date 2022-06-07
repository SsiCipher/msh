#include "msh.h"

void	ft_echo(char *str, int print_newline)
{
	ft_putstr_fd(str, 1);
	if (print_newline)
		ft_putchar_fd('\n', 1);
}

void	ft_cd(char *path, t_env *env)
{
	int		i;
	char	*tmp;
	char	*prev_wd_path;

	prev_wd_path = getcwd(NULL, 0);
	chdir(path);
	i = 0;
	while (env->content[i])
	{
		if (!ft_strncmp(env->content[i], "PWD=", 4))
		{
			tmp = env->content[i];
			env->content[i] = ft_strdup(path);
			free(tmp);
		}
		else if (!ft_strncmp(env->content[i], "OLDPWD=", 7))
		{
			tmp = env->content[i];
			env->content[i] = ft_strdup(prev_wd_path);
			free(tmp);
		}
		i++;
	}
	free(prev_wd_path);
}

void	ft_pwd(void)
{
	char	*current_wd;

	current_wd = getcwd(NULL, 0);
	ft_putendl_fd(current_wd, 1);
	free(current_wd);
}

void	ft_export(char *new_var, t_env *env)
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
