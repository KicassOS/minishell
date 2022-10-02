/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:07:40 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/02 17:54:39 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_env(t_list **env)
{
	t_list	*current;

	current = *env;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
