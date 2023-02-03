/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:18:58 by pszleper          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(char **args)
{
	char	*pwd;
	int		arg_count;

	arg_count = ft_count_subarrays(args);
	if (arg_count > 1)
	{
		ft_printf_stderr("%s: %s\n", SHELL, "pwd: too many arguments");
		return (EXIT_FAILURE);
	}
	pwd = ft_getcwd();
	printf("%s\n", pwd);
	ft_free((void **)&pwd);
	return (EXIT_SUCCESS);
}
