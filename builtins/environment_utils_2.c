/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 05:03:32 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/04 11:28:43 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Simple utility function made for ft_get_env_variable_value
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
	if (i == ft_strlen(content))
		return (NULL);
	value = ft_substr(content, i + 1, ft_strlen(content) - i + 2);
	return (value);
}

/*
  Modifies the node containing oldval, changing it's content to newval
  Returns the address of the node in question or NULL if it couldn't find it
*/
t_list	*ft_modify_env_var_value(t_list **my_env, char *oldval, char *newval)
{
	t_list	*current;

	while (current)
	{
		if (ft_strncmp(current->content, oldval, ft_strlen(oldval)) == 0)
		{
			//ft_free((void **) current_content); UNCOMMENT THIS ONCE THE PARSING IS DONE
			current->content = newval;
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

/*
	Returns 1 if the environment variable name passed as argument is valid
	Returns 0 if it isn't
*/
char	ft_is_valid_env_variable(char *variable)
{
	int	i;

	if (ft_isdigit((int) variable[0]))
		return (0);
	i = 0;
	while (variable[i])
	{
		if (!ft_isalnum(variable[i]) && variable[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
