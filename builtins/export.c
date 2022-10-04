/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/04 13:36:23 by pszleper         ###   ########.fr       */
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

static void	ft_main_loop(t_list **my_env, char **args, int i)
{
	t_list	*new_node;
	char	*var_name;

	var_name = ft_extract_variable_name(args[i]);
	if (!ft_find_env_variable(my_env, var_name))
	{
		new_node = ft_env_new_node((void *) args[i]);
		ft_lstadd_back(my_env, new_node);
	}
	else
		ft_modify_env_var_value(my_env, var_name, args[i]);
	ft_free((void **) &var_name);
}

// add modification of env values
char	ft_export(t_list **my_env, char **args)
{
	int		arg_count;
	int		i;

	if (!args || !args[0])
	{
		ft_print_env_declarations(*my_env);
		return (EXIT_SUCCESS);
	}
	arg_count = ft_count_subarrays(args);
	i = 0;
	while (i < arg_count)
	{
		ft_main_loop(my_env, args, i);
		i++;
	}
	return (EXIT_SUCCESS);
}
