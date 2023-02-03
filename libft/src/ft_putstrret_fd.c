/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrret_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:14:20 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 16:14:21 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstrret_fd(char *s, int fd)
{
	if (s == NULL)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}
