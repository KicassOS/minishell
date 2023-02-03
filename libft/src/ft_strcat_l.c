/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:15:18 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 16:15:19 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcat_l(char *dst, const char *src, size_t dstsize)
{
	size_t	ld;
	size_t	i;
	size_t	ls;

	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	if (dstsize <= ld)
		return (dstsize + ft_strlen(src));
	i = 0;
	while (ld < dstsize - 1 && src[i] != '\0')
	{
		dst[ld] = src[i];
		ld++;
		i++;
	}
	dst[ld] = '\0';
	return (ft_strlen(dst) + ls - i);
}
