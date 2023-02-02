/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:12 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/21 04:17:35 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (needle[0] == '\0')
		return ((char *) haystack);
	while (haystack[j] && i < len)
	{
		while (haystack[j] && haystack[j] == needle[k] && (i + j) < len)
		{
			if (needle[k + 1] == '\0')
				return ((char *) haystack + j - k);
			j++;
			k++;
		}
		j = 0;
		k = 0;
		haystack++;
		i++;
	}
	return (NULL);
}

static void	ft_print_env_declarations(t_slist *my_env)
{
	t_slist	*current;

	current = my_env;
	while (current)
	{
		if (!ft_strnstr(current->content, "_=", ft_strlen(current->content)))
			printf("declare -x %s\n", (char *) current->content);
		current = current->next;
	}
}

static void	ft_main_loop(t_slist **my_env, char **args, int i)
{
	t_slist	*new_node;
	char	*var_name;

	var_name = ft_extract_variable_name(args[i]);
	if (!ft_find_env_variable(my_env, var_name))
	{
		new_node = ft_env_new_node((void *) ft_strdup(args[i]));
		ft_lstadd_back(my_env, new_node);
		ft_free((void **) &var_name);
	}
	else
	{
		ft_overwrite_env_var_value(my_env, var_name, ft_strdup(args[i]));
		free(var_name);
		var_name = NULL;
	}
}

// add modification of env values
int	ft_export(t_slist **my_env, char **args)
{
	int		arg_count;
	int		i;

	if (!args || !args[1] || !args[1][0])
	{
		ft_print_env_declarations(*my_env);
		ft_free_args(args);
		if (args && args[0])
		{
			free(args[0]);
			free(args);
		}
		return (EXIT_SUCCESS);
	}
	arg_count = ft_count_subarrays(args);
	i = 1;
	while (i < arg_count)
	{
		ft_main_loop(my_env, args, i);
		i++;
	}
	return (EXIT_SUCCESS);
}
