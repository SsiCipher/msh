#include "msh.h"

char	*ft_str_replace(char *str, char *find, char *replace)
{
	int find_len = ft_strlen(find);
	int str_len = ft_strlen(str);

	char *find_i = ft_strstr(str, find);
	char *start = ft_substr(str, 0, find_i - str);
	char *end = ft_substr(str, (unsigned int)(find_i - str) + find_len, str_len);
	char *output = ft_strjoin(start, replace);
	output = ft_strjoin(output, end);
	return (output);
}

/**
 * find and replace all variables in str
 * @param str the string to use
 * @param env t_env struct containing environment variables
 * @return str string with variables replaced with their values
 */
char	*expand_vars(char *str, t_env *env)
{
	int		i = 0;
	int		var_len;
	char	*var;

	while (str[i])
	{
		var_len = 0;
		if (str[i] == '$')
		{
			i += 1;
			while (
				ft_isalnum(str[i + var_len])
				|| str[i + var_len] == '_'
			)
				var_len += 1;
			if (var_len == 0)
				i++;
			else
			{
				var = ft_substr(str, i - 1, var_len + 1);
				str = ft_str_replace(str, var, get_env_var(env, var + 1));
				i += var_len;
			}
		}
		else
			i++;
	}
	return (str);
}