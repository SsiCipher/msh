/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:14:26 by yanab             #+#    #+#             */
/*   Updated: 2022/01/24 08:18:01 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		str_len;
	char	*mapped_str;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	mapped_str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!mapped_str)
		return (NULL);
	i = -1;
	while (s[++i])
		mapped_str[i] = f(i, s[i]);
	mapped_str[i] = '\0';
	return (mapped_str);
}
