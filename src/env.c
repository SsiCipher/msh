/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:27:33 by yanab             #+#    #+#             */
/*   Updated: 2022/08/17 08:14:12 by cipher           ###   ########.fr       */
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
 * Check if the current env_line's name matches name
 *  
 * @param	env_line the line to check
 * @param	name the name of the variable to search for
 * @return	true if the names match, false otherwise
*/
bool	is_var(char *env_line, char *name)
{
	int		name_len;

	name_len = ft_strlen(name);
	return (
		!ft_strncmp(env_line, name, name_len)
		&& (
			env_line[name_len] == '\0'
			|| env_line[name_len] == '='
		)
	);
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

	i = 0;
	while (i < env->length)
	{
		if (is_var(env->content[i], name))
			return (true);
		i++;
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
		edit_var(env, name, value, false);
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
 * @param	append true to append the value to the variable
 */
void	edit_var(t_env *env, char *name, char *value, bool append)
{
	size_t	i;
	char	*tmp;

	if (!contains_var(env, name))
		add_var(env, name, value);
	else
	{
		if (!value)
			return ;
		i = -1;
		while (++i < env->length)
		{
			if (is_var(env->content[i], name))
			{
				tmp = env->content[i];
				if (!append && value)
					env->content[i] = ft_strjoin_many(3, name, "=", value);
				else if (!append && !value)
					env->content[i] = ft_strdup(name);
				else
				{
					if (ft_indexof(env->content[i], '=') == -1)
						env->content[i] = ft_strjoin_many(3, env->content[i], "=", value);
					else
						env->content[i] = ft_strjoin(env->content[i], value);
				}
				free(tmp);
			}
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
	char	**new_content;

	if (contains_var(env, name))
	{
		i = -1;
		j = 0;
		new_content = (char **)malloc(sizeof(char *) * env->length - 1);
		while (++i < env->length)
		{
			if (is_var(env->content[i], name))
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
