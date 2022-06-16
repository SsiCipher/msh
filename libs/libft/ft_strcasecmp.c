#include "libft.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (toupper(s1[i]) != toupper(s2[i]))
			break ;
		i++;
	}
	return ((unsigned char)toupper(s1[i]) -(unsigned char)toupper(s2[i]));
}
