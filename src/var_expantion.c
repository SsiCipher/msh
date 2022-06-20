#include "msh.h"

/**
 * find and replace the first occurence of 'find' in str by 'replace'
 * 
 * @param	str the string to use
 * @param	find the search word
 * @param	replace the word to repleace it with
 * @return	the new string allocated in memory
 */
char	*ft_find_n_replace(char *str, char *find, char *replace)
{
	char	*find_i;
	char	*start;
	char	*end;
	char	*output;

	find_i = ft_strstr(str, find);
	start = ft_substr(str, 0, find_i - str);
	end = ft_substr(str, (unsigned int)(find_i - str) + ft_strlen(find), ft_strlen(str));
	output = ft_strjoin_many(3, start, replace, end);
	free(start);
	free(end);
	return (output);
}

/**
 * find and replace all variables in str
 * 
 * @param	str the string to use
 * @param	env t_env struct containing environment variables
 * @return	str string with variables replaced with their values
 */
char	*expand_vars(char *str, t_env *env)
{
	int		i = 0;
	int		var_len;
	char	*var;
	char	*var_value;

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
				var_value = get_env_var(env, var + 1);
				str = ft_find_n_replace(str, var, var_value);
				free(var);
				free(var_value);
				i += var_len;
			}
		}
		else
			i++;
	}
	return (str);
}
