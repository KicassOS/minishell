/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:18:58 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/03 04:35:23 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 4096);
	if (buffer == NULL)
	{
		perror(NULL);
		exit(PWD_ERROR);
	}
	buffer = getcwd(buffer, 4096);
	if (buffer == NULL)
	{
		perror(NULL);
		exit(errno);
	}
	else
		printf("%s\n", buffer);
}
