/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:35:46 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/21 04:27:19 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args)
{
	if (args[1][0] && ft_strnstr(args[1], "-n", 2))
		printf("%s", args[0]);
	else
		printf("%s\n", args[0]);
	ft_free_args(args);
	return (EXIT_SUCCESS);
}
