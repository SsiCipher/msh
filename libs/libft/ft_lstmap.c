/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:36:58 by yanab             #+#    #+#             */
/*   Updated: 2021/11/15 22:02:40 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		i;
	t_list	*new_list;
	t_list	*new_item;

	if (!lst || !f)
		return (NULL);
	i = 0;
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	lst = lst->next;
	while (lst != NULL)
	{
		new_item = ft_lstnew(f(lst->content));
		if (!new_list)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_item);
		i++;
		lst = lst->next;
	}
	return (new_list);
}
