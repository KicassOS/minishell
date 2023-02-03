/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:17:06 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 14:17:07 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_slist	*ft_lstmap(t_slist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_slist	*new;
	t_slist	*tmp;

	new = 0;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
			ft_lstclear(&new, del);
		else
			ft_lstadd_back(&new, tmp);
		lst = lst->next;
	}
	return (new);
}
