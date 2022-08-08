/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:27:33 by yanab             #+#    #+#             */
/*   Updated: 2022/08/08 12:01:21 by cipher           ###   ########.fr       */
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
	new_envp->content[i] = NULL;
	return (new_envp);
}

/**
 * Free the allocated memory for the copied envp
 * 
 * @param	env t_env struct that holds the new copy of the envp
 */
void	delete_env(t_env **env)
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
 * @param	name the name of the variable to search for
 * @return	the value of the variable if found or NULL
 */
char	*get_var(t_env *env, char *name)
{
	size_t	i;
	int		name_len;
	char	*var_value;

	i = 0;
	name_len = ft_strlen(name);
	while (env->content[i])
	{
		if (!ft_strncmp(env->content[i], name, name_len))
		{
			if (env->content[i][name_len] == '\0')
				return (NULL);
			else if (env->content[i][name_len] == '=')
			{
				var_value = ft_substr(env->content[i],
						name_len + 1, ft_strlen(env->content[i]));
				return (var_value);
			}
		}
		i++;
	}
	return (NULL);
}

/**
 * Checks if a variable is in the env
 * 
 * @param	env t_env struct that holds all the environment variables
 * @param	name the name of the variable to search for
 * @return	true if the variable was found false if not
 */
bool	contains_var(t_env *env, char *name)
{
	size_t	i;
	int		name_len;

	i = -1;
	name_len = ft_strlen(name);
	while (++i < env->length)
	{
		if (!ft_strncmp(env->content[i], name, name_len)
			&& (env->content[i][name_len] == '\0'
			|| env->content[i][name_len] == '=')
		)
			return (true);
	}
	return (false);
}

/**
 * Checks if a variable is in the env
 * 
 * @param	env t_env struct that holds all the environment variables
 * @param	name the name of the variable to search for
 * @param	value the new value to use
 * @return	true if the variable was found false if not
 */
void	add_var(t_env *env, char *name, char *value)
{
	if (contains_var(env, name))
		edit_var(env, name, value, true);
	else
	{
		env->content = (char **)ft_realloc(env->content,
				env->length * sizeof(char *),
				(env->length + 2) * sizeof(char *));
		if (value)
			env->content[env->length] = ft_strjoin_many(3, name, "=", value);
		else
			env->content[env->length] = ft_strdup(name);
		env->content[env->length + 1] = NULL;
		env->length += 1;
	}
}

/**
 * Change the value of a variable in the env
 * 
 * @param	env t_env struct that holds all the environment variables
 * @param	name the name of the variable to edit for
 * @param	value the new value to use
 * @param	truncate true to truncate the value of the variable
 */
void	edit_var(t_env *env, char *name, char *value, bool truncate)
{
	size_t	i;
	char	*tmp;
	int		name_len;

	i = -1;
	name_len = ft_strlen(name);
	while (++i < env->length)
	{
		if (
			!ft_strncmp(env->content[i], name, name_len)
			&& (env->content[i][name_len] == '\0'
			|| env->content[i][name_len] == '=')
		)
		{
			tmp = env->content[i];
			if (truncate)
				env->content[i] = ft_strjoin_many(3, name, "=", value);
			else
				env->content[i] = ft_strjoin(env->content[i], value);
			free(tmp);
		}
	}
}

/**
 * Delete a variable from the env
 * 
 * @param	env t_env struct that holds all the environment variables
 * @param	name the name of the variable to edit for
 */
void	delete_var(t_env *env, char *name)
{
	size_t	i;
	size_t	j;
	int		name_len;
	char	**new_content;

	if (contains_var(env, name))
	{
		i = -1;
		j = 0;
		name_len = ft_strlen(name);
		new_content = (char **)malloc(sizeof(char *) * env->length - 1);
		while (++i < env->length)
		{
			if (!ft_strncmp(env->content[i], name, name_len)
				&& (env->content[i][name_len] == '\0'
				|| env->content[i][name_len] == '='))
				free(env->content[i]);
			else
				new_content[j++] = env->content[i];
		}
		new_content[j] = NULL;
		free(env->content);
		env->length -= 1;
		env->content = new_content;
	}
}
