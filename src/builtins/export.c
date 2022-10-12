/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/10/12 22:04:07 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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
	char	**tmp_env;

	i = -1;
	tmp_env = malloc(sizeof(char *) * env->length);
	ft_memmove(tmp_env, env->content, sizeof(char *) * env->length);
	ft_qsort_str(tmp_env, env->length, ft_strcmp);
	while (++i < env->length)
	{
		eq_i = ft_indexof(tmp_env[i], '=');
		if (eq_i == -1)
			printf("declare -x %s\n", tmp_env[i]);
		else
			printf("declare -x %.*s=\"%s\"\n", eq_i, tmp_env[i],
				&tmp_env[i][eq_i + 1]);
	}
}

int	ft_export(int argc, char **argv, t_env *env)
{
	size_t	i;
	char	*tmp;
	char	*name;
	char	*value;
	bool	append;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
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
				exit_code = builtin_error("export", tmp, "is not a valid identifier", 1);
			free(tmp);
		}
	}
	return (exit_code);
}
