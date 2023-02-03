/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:53:56 by pszleper          #+#    #+#             */
/*   Updated: 2023/02/03 19:48:33 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(t_slist **my_env, char **args)
{
	int		arg_count;
	int		i;
	char	*var_name;

	arg_count = ft_count_subarrays(args);
	i = 1;
	while (i < arg_count)
	{
		var_name = ft_extract_variable_name_export(args[i]);
		ft_delete_env_node(my_env, var_name);
		free(var_name);
		i++;
	}
	return (EXIT_SUCCESS);
}
