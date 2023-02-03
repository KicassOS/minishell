/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:22:38 by pszleper          #+#    #+#             */
/*   Updated: 2023/02/03 16:57:39 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
  This function handles the case where the argument passed to export has no 
  equal sign, and adds an equal sign to it at the end.
  For example: export test --> test=
*/
char	*ft_sanitize_var_name(char *str)
{
	int		i;
	bool	equal_sign_present;
	char	*newstr;

	i = 0;
	newstr = NULL;
	equal_sign_present = false;
	while (str[i])
	{
		if (str[i] == '=')
			equal_sign_present = true;
		i++;
	}
	if (equal_sign_present == false)
	{
		newstr = ft_strjoin(str, "=");
		free(str);
		return (newstr);
	}
	return (str);
}

/*
  Same as the other one, but doesn't return NULL if the index of the equal sign
  is equal to the length of the string
*/
char	*ft_extract_variable_name_export(char *content)
{
	int		i;
	char	*name;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	if (i == 0)
		return (NULL);
	name = ft_substr(content, 0, i);
	return (name);
}
