/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:35:46 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/21 16:03:28 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_newlineflag(char **args, int *print_newline, int *i)
{
	if (ft_strlen(args[0]) == 2 && ft_strnstr(args[0], "-n", 2))
	{
		*print_newline = 0;
		*i += 1;
	}
}

int	ft_echo(char **args)
{
	int	print_newline;
	int	i;

	if (*args)
		args++;
	print_newline = 1;
	i = 0;
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
//	ft_free_args(args);
	return (EXIT_SUCCESS);
}
