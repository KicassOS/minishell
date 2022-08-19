/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:35:46 by pszleper          #+#    #+#             */
/*   Updated: 2022/08/19 20:33:49 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *argument, char *flag)
{
	if (ft_strnstr(flag, "-n", ft_strlen(flag)))
		printf("%s", argument);
	else
		printf("%s\n", argument);
}
