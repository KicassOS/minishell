/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:06:54 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 16:06:55 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ptrd;
	const char	*ptrs;
	size_t		i;

	ptrd = (char *)dst;
	ptrs = (const char *)src;
	if (!ptrd && !ptrs)
		return (NULL);
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			ptrd[i] = ptrs[i];
			i++;
		}
	}
	if (dst >= src)
	{
		i = len;
		while (i-- != 0)
			ptrd[i] = ptrs[i];
	}
	return ((void *)dst);
}
