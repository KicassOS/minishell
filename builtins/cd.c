/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:50:09 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/03 04:32:09 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char *destination)
{
	int	result;

	result = -200;
	if (!destination)
	{
		return (EXIT_SUCCESS);
	}
	result = chdir(destination);
	if (result != 0)
	{
		perror(NULL);
		exit(CHDIR_ERROR);
	}
}
