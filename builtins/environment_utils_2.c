/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 05:03:32 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/04 13:36:07 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Calls ft_substr to get the part after the equal sign it finds
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
	while (content[i] != '=')
		i++;
	if (i == (int) ft_strlen(content) || i == 0)
		return (NULL);
	name = ft_substr(content, 0, i);
	return (name);
}

/*
  Modifies the node containing oldval, changing its' content to newval
  Returns the address of the node in question or NULL if it couldn't find it
*/
t_list	*ft_modify_env_var_value(t_list **my_env, char *oldval, char *newval)
{
	t_list	*node;

	node = ft_find_env_variable(my_env, oldval);
	if (node == NULL)
		return (NULL);
	//ft_free((void **) &node->content); UNCOMMENT THIS ONCE THE PARSING IS DONE
	node->content = newval;
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
