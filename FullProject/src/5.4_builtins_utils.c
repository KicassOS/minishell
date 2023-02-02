/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.4_builtins_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:06:17 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dlstdel(void *content)
{
	free(content);
}

char	*ft_child_search_myenv(t_slist **my_env, char *var)
{
	t_slist	*current;

	if (*my_env == NULL)
		return (NULL);
	current = *my_env;
	while (current != NULL)
	{
		if (!ft_strcmp_n((char *)current->content, var, ft_strlen(var)))
			return ((char *)current->content);
		current = current->next;
	}
	return (NULL);
}
