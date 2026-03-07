/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 20:04:00 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/22 20:25:37 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_check_content(t_list **lst)
{
	ft_lstclear(lst, free);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map_lst;
	t_list	*map_node;
	void	*f_content;

	if (!lst || !f)
		return (NULL);
	map_lst = NULL;
	while (lst)
	{
		f_content = f(lst->content);
		if (!f_content)
			return (ft_check_content(&map_lst));
		map_node = ft_lstnew(f_content);
		if (!map_node)
		{
			if (del)
				del(f_content);
			ft_lstclear(&map_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&map_lst, map_node);
		lst = lst->next;
	}
	return (map_lst);
}
