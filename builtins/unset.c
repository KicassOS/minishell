/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:53:56 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/03 03:05:48 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_unset(char **myenv, char **args)
{
	int	arg_count;
	int	i;

	arg_count = ft_count_subarrays(args);
	i = 0;
	while (i < arg_count)
	{
		ft_delete_env_node(myenv, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
