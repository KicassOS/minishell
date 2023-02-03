/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:14:50 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 14:14:51 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isnumber(char *str)
{
	int	i;
	int	len;

	if (str == NULL)
		return (false);
	i = 0;
	if (str[i] == '-' && ft_isdigit(str[i + 1]))
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	len = ft_strlen(str);
	if (len == 0 || i < len)
		return (false);
	return (true);
}
