/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:13:38 by yanab             #+#    #+#             */
/*   Updated: 2021/11/14 14:13:38 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		s_len;
	char	*dupicate;

	s_len = ft_strlen(s);
	dupicate = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!dupicate)
		return (NULL);
	ft_memcpy(dupicate, s, s_len);
	dupicate[s_len] = '\0';
	return (dupicate);
}
