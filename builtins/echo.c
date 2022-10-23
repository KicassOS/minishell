/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:35:46 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/23 22:34:02 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **args)
{
	if (args[1][0] && ft_strnstr(args[1], "-n", 2))
		printf("%s", args[0]);
	else
		printf("%s\n", args[0]);
	free(args[0]);
	free(args[1]);
	free(args[2]);
	free(args);
}
