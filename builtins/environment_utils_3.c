/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:54:42 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/12 16:24:46 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Returns a string of the type "name=value" after being passed those 2 args
	name and value must both exist as no checks are done about their existence
*/
char	*ft_create_env_value(char *name, char *value)
{
	char	*env_value;
	int		i;
	int		j;

	env_value = ft_malloc(ft_strlen(name) + ft_strlen(value) + 2);
	i = 0;
	j = 0;
	while (i < (int) ft_strlen(name))
	{
		env_value[i] = name[i];
		i++;
	}
	env_value[i] = '=';
	i++;
	j = 0;
	while (j < (int) ft_strlen(value))
	{
		env_value[i] = value[j];
		i++;
		j++;
	}
	return (env_value);
}

/*
  Creates and adds an environment variable if it doesn't exist
  Does not modify existing variables
  Returns the new_node if created, NULL otherwise
*/
t_list	*ft_add_env_value(t_list **my_env, char *content)
{
	t_list	*new_node;
	char	*name;

	name = ft_extract_variable_name(content);
	if (ft_find_env_variable(my_env, name))
	{
		ft_free((void **) &name);
		return (NULL);
	}
	new_node = ft_overwrite_env_var_value(my_env, content, content);
	ft_free((void **) &name);
	return (new_node);
}
