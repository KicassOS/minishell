/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:17:14 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 14:17:15 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_slist	*ft_lstnew(void *content)
{
	t_slist	*new;

	new = malloc(sizeof(t_slist));
	if (!new)
		return (NULL);
	new->next = (NULL);
	new->content = content;
	return (new);
}
