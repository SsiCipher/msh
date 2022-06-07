/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:11:34 by yanab             #+#    #+#             */
/*   Updated: 2021/11/14 14:11:34 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end_list;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		end_list = ft_lstlast(*lst);
		end_list->next = new;
	}
}
