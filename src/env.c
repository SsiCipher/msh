/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 05:27:33 by yanab             #+#    #+#             */
/*   Updated: 2022/08/18 09:07:37 by cipher           ###   ########.fr       */
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
