/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:53:56 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/21 21:10:06 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_list **my_env, char **args)
{
	int	arg_count;
	int	i;

	arg_count = ft_count_subarrays(args);
	i = 0;
	while (i < arg_count)
	{
		ft_delete_env_node(my_env, args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	return (EXIT_SUCCESS);
}
