/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:21 by yanab             #+#    #+#             */
/*   Updated: 2022/08/27 16:41:55 by cipher           ###   ########.fr       */
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

// TODO: Print variables sorted by ascii

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
			free(tmp);
		}
	}
}
