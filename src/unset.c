/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:53:56 by pszleper          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(t_slist **my_env, char **args)
{
	int	arg_count;
	int	i;

	arg_count = ft_count_subarrays(args);
	i = 1;
	while (i < arg_count)
	{
		ft_delete_env_node(my_env, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
