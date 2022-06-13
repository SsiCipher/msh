#include "msh.h"

t_env	*copy_env(char **envp)
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

char	*get_env_var(t_env *env, char *var_name)
{
	size_t	i;
	char	*var_value;

	i = 0;
	var_name = ft_strjoin(var_name, "=");
	while (i < env->length)
	{
		if (!ft_strncmp(env->content[i], var_name, ft_strlen(var_name)))
		{
			var_value = ft_substr(env->content[i],
					ft_strlen(var_name), ft_strlen(env->content[i]));
			free(var_name);
			return (var_value);
		}
		i++;
	}
	free(var_name);
	return (NULL);
}
