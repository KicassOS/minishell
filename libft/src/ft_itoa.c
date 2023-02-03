/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:15:25 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 14:15:27 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	static_ft_size(int n)
{
	int	size;

	if (!n)
		return (2);
	size = 1;
	if (n < 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static void	static_ft_fill(int size, int n, char *str, int sign)
{
	int	i;

	i = size - 1;
	while (n != 0)
	{
		str[i - 1] = -(n % 10) + '0';
		n = (n - (n % 10)) / 10;
		i--;
	}
	str[size - 1] = '\0';
	if (!sign)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*str;
	int		size;

	size = static_ft_size(n);
	sign = 0;
	if (n > 0)
	{
		sign = 1;
		n = -n;
	}
	str = malloc(sizeof(char) * (size));
	if (!str)
		return (NULL);
	if (!n)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	static_ft_fill(size, n, str, sign);
	return (str);
}
