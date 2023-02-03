/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:53:44 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 19:11:40 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_check_newlineflag(char **args, int *print_newline, int *i)
{
	if (args[1] && ft_memcmp(args[1], "-n\0", 3) == 0)
	{
		*print_newline = 0;
		*i += 1;
	}
}

int	ft_echo(char **args)
{
	int	print_newline;
	int	i;

	if (*args == NULL)
		return (EXIT_SUCCESS);
	print_newline = 1;
	i = 1;
	if (!args)
	{
		ft_free_args(args);
		return (EXIT_SUCCESS);
	}
	ft_check_newlineflag(args, &print_newline, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (print_newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
