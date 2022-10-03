/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 05:03:32 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/03 18:47:37 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_extract_variable_value(char *content)
{
	int		i;
	char	*value;

	i = 0;
	while (content[i] != '=')
		i++;
	value = ft_substr(content, i + 1, ft_strlen(content) - i + 2);
	return (value);
}

char	ft_is_valid_env_variable(char *variable);
//TODO FINISH
