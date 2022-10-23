/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 05:03:32 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/22 23:09:21 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Calls ft_substr to get the part after the equal sign it finds
	as a malloc'd string
	Returns NULL if it reached the end of content without finding an equal
*/
char	*ft_extract_variable_value(char *content)
{
	int		i;
	char	*value;

	i = 0;
	while (content[i] != '=')
		i++;
	if (i == (int) ft_strlen(content))
		return (NULL);
	value = ft_substr(content, i + 1, ft_strlen(content) - i + 2);
	return (value);
}

/*
	Returns variable name as malloc'd string when passed a node's content
	Returns NULL if the equal sign is at the end or very beginning of arg
*/
char	*ft_extract_variable_name(char *content)
{
	int		i;
	char	*name;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	if (i == 0 || i == (int) ft_strlen(content))
		return (NULL);
	name = ft_substr(content, 0, i);
	return (name);
}

/*
  Modifies the node containing oldval, OVERWRITING its' content to newval
  Returns the address of the node in question
  If the node can't be found, creates a new node containing newval
  and adds it to my_env, then returns the node's address
*/
t_list	*ft_overwrite_env_var_value(t_list **my_env, char *oldval, char *newval)
{
	t_list	*node;

	node = ft_find_env_variable(my_env, oldval);
	if (node == NULL)
	{
		node = ft_env_new_node((void *) newval);
		ft_lstadd_back(my_env, node);
		if (ft_strncmp(oldval, newval, ft_strlen(oldval)) != 0)
			ft_free((void **) oldval);
		return (node);
	}
	ft_free((void **) &node->content);
	node->content = newval;
	return (node);
}

/*
  Modifies the node with name "name", changing its' content to "value"
  name and value must be malloc'd strings
  Returns the address of the node in question
  If the node can't be found, creates a new node containing newval
  and adds it to my_env, then returns the node's address
*/
t_list	*ft_modify_env_var_value(t_list **my_env, char *name, char *value)
{
	t_list	*node;
	char	*env_value;

	node = ft_find_env_variable(my_env, name);
	env_value = ft_create_env_varstring(name, value);
	if (node == NULL)
	{
		node = ft_env_new_node((void *) env_value);
		ft_lstadd_back(my_env, node);
		return (node);
	}
	ft_free((void **) &node->content);
	ft_free((void **) &name);
	ft_free((void **) &value);
	node->content = env_value;
	return (node);
}

/*
	Returns 1 if the node content string passed as argument is valid
	Returns 0 if it isn't
*/
char	ft_is_valid_env_variable(char *content)
{
	int	i;

	if (ft_isdigit((int) content[0]))
		return (0);
	i = 0;
	while (content[i])
	{
		if (!ft_isalnum(content[i]) && content[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
