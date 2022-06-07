#include "msh.h"

t_env	*dup_env(char **envp)
{
	int		i;
	t_env	*new_envp;

	new_envp = malloc(sizeof(t_env));

	new_envp->length = 0;
	while (envp[new_envp->length])
		new_envp->length += 1;

	i = -1;
	new_envp->content = (char **)malloc(sizeof(char *) * (new_envp->length + 1));
	while (envp[++i])
		new_envp->content[i] = ft_strdup(envp[i]);
	envp[i] = NULL;

	return (new_envp);
}

char *get_env_var(t_env *env, char *var_name)
{
	char *var_value;

	var_name = ft_strjoin(var_name, "=");
	for (size_t i = 0; i < env->length; i++)
	{
		if (!ft_strncmp(env->content[i], var_name, ft_strlen(var_name)))
		{
			var_value = ft_substr(env->content[i], ft_strlen(var_name), ft_strlen(env->content[i]));
			free(var_name);
			return (var_value);
		}
	}
	free(var_name);
	return (NULL);
}
