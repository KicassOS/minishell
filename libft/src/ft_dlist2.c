/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:13:44 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 14:13:45 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	t_dlist	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp != NULL)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}

void	ft_dlstremove_node(t_dlist **lst, t_dlist *node_to_remove,
	void (*del)(void *))
{
	if (*lst == node_to_remove)
	{
		*lst = node_to_remove->next;
		if (*lst != NULL)
			(*lst)->prev = NULL;
	}
	else
	{
		node_to_remove->prev->next = node_to_remove->next;
		if (node_to_remove->next != NULL)
			node_to_remove->next->prev = node_to_remove->prev;
	}
	node_to_remove->next = NULL;
	node_to_remove->prev = NULL;
	del(node_to_remove->content);
	node_to_remove->content = NULL;
	free(node_to_remove);
	return ;
}

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*tmp;
	t_dlist	*next;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		next = tmp->next;
		ft_dlstremove_node(lst, tmp, del);
		tmp = next;
	}
	*lst = NULL;
}
