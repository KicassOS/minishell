/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:16:29 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 14:16:30 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_slist *lst, void (*del)(void *))
{
	del(lst->content);
	lst->content = NULL;
	lst->next = NULL;
	free(lst);
}
