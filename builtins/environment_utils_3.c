/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:54:42 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/06 23:33:52 by pszleper         ###   ########.fr       */
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
