/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:27:33 by yanab             #+#    #+#             */
/*   Updated: 2022/08/01 19:37:50 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/**
 * Create a copy of the envp variable
 * 
 * @param	envp the list of environment variables to duplicate
 * @return	t_env struct that holds the new copy of the envp
 */
t_env	*create_env(char **envp)
{
	int		i;
	t_env	*new_envp;

	new_envp = malloc(sizeof(t_env));
	new_envp->length = 0;
	while (envp[new_envp->length])
		new_envp->length += 1;
	i = -1;
	new_envp->content = (char **)malloc(
			sizeof(char *) * (new_envp->length + 1));
	while (envp[++i])
		new_envp->content[i] = ft_strdup(envp[i]);
	envp[i] = NULL;
	return (new_envp);
}

/**
 * Free the allocated memory for the copied envp
 * 
 * @param	env t_env struct that holds the new copy of the envp
 */
void	free_env(t_env **env)
{
	int		i;

	i = -1;
	while ((*env)->content[++i])
		free((*env)->content[i]);
	free((*env)->content);
	free(*env);
	*env = NULL;
}

/**
 * Searches for a variable in the env
 * 
 * @param	env t_env struct that holds all the environment variables
 * @param	var_name the name of the variable to search for
 * @return	the value of the variable if found or NULL
 */
char	*get_var(t_env *env, char *var_name)
{
	size_t	i;
	int		var_name_len;
	char	*var_value;

	i = -1;
	var_name = ft_strjoin(var_name, "=");
	var_name_len = ft_strlen(var_name);
	while (++i < env->length)
	{
		if (!ft_strncmp(env->content[i], var_name, var_name_len))
		{
			var_value = ft_substr(env->content[i],
					var_name_len, ft_strlen(env->content[i]));
			free(var_name);
			return (var_value);
		}
	}
	free(var_name);
	return (NULL);
}

bool	contains_var(t_env *env, char *var_name)
{
	size_t	i;

	i = -1;
	var_name = ft_strjoin(var_name, "=");
	while (++i < env->length)
	{
		if (!ft_strncmp(env->content[i], var_name, ft_strlen(var_name)))
		{
			free(var_name);
			return (true);
		}
	}
	free(var_name);
	return (false);
}

void	edit_var(t_env *env, char *var_name, char *new_value)
{
	size_t	i;
	int		var_name_len;

	i = -1;
	var_name = ft_strjoin(var_name, "=");
	var_name_len = ft_strlen(var_name);
	while (++i < env->length)
	{
		if (!ft_strncmp(env->content[i], var_name, var_name_len))
		{
			free(env->content[i]);
			env->content[i] = ft_strjoin(var_name, new_value);
		}
	}
	free(var_name);
}

void	delete_var(t_env *env, char *var_name)
{
	size_t	i;
	size_t	j;
	char	**new_content;

	if (contains_var(env, var_name))
	{
		i = -1;
		j = 0;
		var_name = ft_strjoin(var_name, "=");
		new_content = (char **)malloc(sizeof(char *) * env->length - 1);
		while (++i < env->length)
		{
			if (ft_strncmp(env->content[i], var_name, ft_strlen(var_name)))
				new_content[j++] = env->content[i];
			else
				free(env->content[i]);
		}
		new_content[j] = NULL;
		free(env->content);
		env->length -= 1;
		env->content = new_content;
		free(var_name);
	}
}
