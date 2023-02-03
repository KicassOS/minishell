/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:52:00 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_builtin_errormessage(char *builtin, char *message)
{
	ft_printf_stderr("%s: %s: %s\n", SHELL, builtin, message);
	return (EXIT_FAILURE);
}

int	ft_errormessage(char *message)
{
	ft_printf_stderr("%s: %s\n", SHELL, message);
	return (EXIT_FAILURE);
}

char	*ft_error_dlst(t_dlist **dlist)
{
	ft_dlstclear(dlist, &ft_dlstdel);
	return (NULL);
}
