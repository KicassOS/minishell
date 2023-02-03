/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:52:49 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:44:37 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_relstclear(t_re **re, void (*del)(void *))
{
	t_re	*temp1;
	t_re	*temp2;

	temp1 = *re;
	if (*re == NULL || del == 0)
		return ;
	while (temp1->next != NULL)
	{
		temp2 = temp1->next;
		ft_relstdelone(temp1, del);
		temp1 = temp2;
	}
	ft_relstdelone(temp1, del);
	*re = NULL;
	return ;
}

t_re	*ft_relstnew(int operator, char *file)
{
	t_re	*result;

	result = malloc(sizeof(t_re));
	if (result == NULL)
		return (NULL);
	(*result).operator = operator;
	(*result).file = file;
	(*result).next = NULL;
	return (result);
}

void	ft_relstadd_back(t_re **re, t_re *new)
{
	t_re	*temp;

	temp = *re;
	if (new == NULL)
		return ;
	if (temp == NULL)
	{
		*re = new;
		return ;
	}
	while ((*temp).next != NULL)
		temp = (*temp).next;
	(*temp).next = new;
}
