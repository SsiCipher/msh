/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_many.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:08:58 by yanab             #+#    #+#             */
/*   Updated: 2022/06/27 06:09:56 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_many(int strs_count, ...)
{
	va_list	ap;
	int		i;
	char	*output;
	int		total_len;

	output = NULL;
	total_len = 0;
	va_start(ap, strs_count);
	i = -1;
	while (++i < strs_count)
		total_len += ft_strlen(va_arg(ap, char *));
	va_end(ap);
	output = (char *)ft_calloc(total_len + 1, sizeof(char));
	va_start(ap, strs_count);
	i = -1;
	while (++i < strs_count)
		ft_strlcat(output, va_arg(ap, char *), total_len + 1);
	va_end(ap);
	return (output);
}
