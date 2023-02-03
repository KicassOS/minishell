/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:52:42 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_addto_lst(t_slist **lst, char *str)
{
	ft_lstadd_back(lst, ft_lstnew(str));
}

int	ft_strindexrev(const char *str, int c)
{
	int		index;
	char	*s1;

	index = ft_strlen(str);
	s1 = (char *)str;
	while (s1[index] != c && index > 0)
	{
		index--;
	}
	if (s1[index] == c)
		return (index);
	else
		return (-1);
}

int	ft_strindex(const char *str, int c)
{
	int		index;
	char	*s1;

	index = 0;
	s1 = (char *)str;
	while (s1[index] != c && s1[index] != '\0')
	{
		index++;
	}
	if (s1[index] == c)
		return (index);
	else
		return (-1);
}
