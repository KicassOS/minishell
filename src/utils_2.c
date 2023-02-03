/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:52:55 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_del(void *content)
{
	free(content);
}

void	ft_delre(char *file)
{
	free (file);
}

void	ft_relstdelone(t_re *re, void (*del)(void *))
{
	if (re == NULL || del == 0)
		return ;
	re->operator = 0;
	(*ft_delre)(re->file);
	free(re);
}
