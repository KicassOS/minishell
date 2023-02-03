/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:15:53 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 16:15:54 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_n(const char *str1, const char *str2, size_t n)
{
	unsigned int	count;

	count = 0;
	while (count < n)
	{
		if ((unsigned char)str1[count] != (unsigned char)str2[count])
		{
			return ((unsigned char)str1[count] - (unsigned char)str2[count]);
		}
		if ((unsigned char)str1[count] == '\0'
			|| (unsigned char)str2[count] == '\0')
		{
			return (0);
		}
		count++;
	}
	return (0);
}
