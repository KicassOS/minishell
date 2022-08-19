/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:50:09 by pszleper          #+#    #+#             */
/*   Updated: 2022/08/19 21:05:36 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char *destination)
{
	int	result;

	result = -200;
	result = chdir(destination);
	if (result != 0)
	{
		perror(NULL);
		exit(errno);
	}
}
