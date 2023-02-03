/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:20:01 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 16:20:03 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy_c(void *dest, const void *src, int c, size_t n)
{
	const unsigned char	*ptrs;
	unsigned char		*ptrd;
	size_t				i;

	ptrs = (unsigned char *)src;
	ptrd = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		ptrd[i] = ptrs[i];
		if (ptrs[i] == (unsigned char)c)
		{
			return (ptrd + i + 1);
		}
		i++;
	}
	return (0);
}
