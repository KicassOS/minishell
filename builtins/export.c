/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/03 03:51:12 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_env_declarations(t_list *my_env)
{
	t_list	*current;

	current = my_env;
	while (current)
	{
		if (!ft_strnstr(current->content, "_=", ft_strlen(current->content)))
			printf("declare -x %s\n", (char *)current->content);
		current = current->next;
	}
}

char	ft_export(t_list *my_env, char **args)
{
	int		arg_count;
	t_list	*new_node;
	int		i;

	if (!args || !args[0])
	{
		ft_print_env_declarations(my_env);
		return (EXIT_SUCCESS);
	}
	arg_count = ft_count_subarrays(args);
	i = 0;
	while (i < arg_count)
	{
		if (ft_not_duplicate(my_env, args[i]))
		{
			new_node = ft_env_new_node((void *) args[i]);
			ft_lstadd_back(&my_env, new_node);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
