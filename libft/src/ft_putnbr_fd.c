/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:13:58 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 16:13:59 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n_unsigned;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n_unsigned = -n;
	}
	else
	{
		n_unsigned = n;
	}
	if (n_unsigned >= 10)
	{
		ft_putnbr_fd(n_unsigned / 10, fd);
		ft_putnbr_fd(n_unsigned % 10, fd);
	}
	else
		ft_putchar_fd(n_unsigned + '0', fd);
}
