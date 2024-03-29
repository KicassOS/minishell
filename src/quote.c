/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:50:32 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	static_remove_quotes(char *str, int j)
{
	int		i;
	char	quote;

	quote = str[j];
	while (str[j + 1] != quote)
	{
		str[j] = str[j + 1];
		j++;
	}
	i = 0;
	while (str[j + 2 + i] != '\0')
	{
		str[j + i] = str[j + 2 + i];
		i++;
	}
	str[j + i] = '\0';
	return (j);
}

void	ft_quoteremover(char **command)
{
	int	i;
	int	j;

	i = 0;
	while (command[i] != NULL)
	{
		j = 0;
		while (command[i][j] != '\0')
		{
			if (command[i][j] == '\'' || command[i][j] == '\"')
				j = static_remove_quotes(command[i], j);
			else
				j++;
		}
		i++;
	}
}
