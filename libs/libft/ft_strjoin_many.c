#include "libft.h"

char *ft_strjoin_many(int strs_count, ...)
{
	va_list	ap;
	char	*output;
	int		total_len;

	output = NULL;
	total_len = 0;
	va_start(ap, strs_count);
	for (int i = 0; i < strs_count; i++)
		total_len += ft_strlen(va_arg(ap, char *));
	va_end(ap);
	output = (char *)ft_calloc(total_len + 1, sizeof(char));
	va_start(ap, strs_count);
	for (int i = 0; i < strs_count; i++)
		ft_strlcat(output, va_arg(ap, char *), total_len + 1);
	va_end(ap);
	return (output);
}
