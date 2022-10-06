/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 03:49:39 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/06 06:20:27 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_subarrays(char **args)
{
	int	i;

	i = 0;
	while (args[i] && args[i][0])
		i++;
	return (i);
}

char	*ft_getcwd(void)
{
	char	*cwd_string;

	cwd_string = getcwd(NULL, 0);
	if (cwd_string == NULL)
	{
		perror(NULL);
		exit(PWD_ERROR);
	}
	return (cwd_string);
}
