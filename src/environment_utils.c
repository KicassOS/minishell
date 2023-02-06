/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 03:49:29 by pszleper          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
  same as libft's ft_lstnew, but prints error message and exits on malloc error
*/
t_slist	*ft_env_new_node(void *content)
{
	t_slist	*element;

	element = ft_malloc(sizeof(t_slist));
	element->content = content;
	element->next = NULL;
	return (element);
}

/*
  Returns a pointer to the t_list struct whose variable name is to_find
  Returns NULL if it couldn't find the node
*/
t_slist	*ft_find_env_variable(t_slist **env, char *to_find)
{
	t_slist	*current;
	char	*var_name;

	current = *env;
	while (current)
	{
		var_name = ft_extract_variable_name_export(current->content);
		if (ft_strncmp(var_name, to_find, ft_strlen(to_find)) == 0)
		{
			ft_free((void **) &var_name);
			return (current);
		}
		ft_free((void **) &var_name);
		current = current->next;
	}
	return (NULL);
}

/*
  Returns a pointer to the t_list struct whose variable name is 'name'
  name must be a malloc'd string
  Returns NULL if it didn't find the struct
*/
t_slist	*ft_find_env_variable_by_name(t_slist **env, char *name_tofind)
{
	t_slist	*current;
	char	*current_name;

	current = *env;
	while (current)
	{
		current_name = ft_extract_variable_name_export(current->content);
		if (ft_strcmp(name_tofind, current_name) == true
			&& ft_strlen(name_tofind) == ft_strlen(current_name))
		{
			free(current_name);
			return (current);
		}
		current = current->next;
	}
	free(current_name);
	return (NULL);
}

/*
  Deletes environment node containing needle
  No error if the function couldn't find any such node
  Function argument MUST be non-NULL as no check is done on their existence
*/
void	ft_delete_env_node(t_slist **env, char *needle)
{
	t_slist	*current;
	t_slist	*before_node;
	t_slist	*next_node;

	current = *env;
	while (current)
	{
		if (current->next)
		{
			if (ft_strncmp(current->next->content,
					needle, ft_strlen(needle)) == 0)
			{
				before_node = current;
				current = current->next;
				next_node = current->next;
				free(current->content);
				free(current);
				before_node->next = next_node;
				return ;
			}
		}
		current = current->next;
	}
}

/*
	Finds the node in the environment my_env whose name is needle
	Returns the part after the = as a malloc'd string
	Returns NULL if it couldn't find the node
*/
char	*ft_get_env_variable_value(t_slist **my_env, char *needle)
{
	t_slist	*search_result;
	char	*env_value;

	search_result = ft_find_env_variable(my_env, needle);
	if (search_result == NULL)
		return (NULL);
	env_value = ft_extract_variable_value(search_result->content);
	return (env_value);
}
