/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:35:22 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/03 04:32:24 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  returns num_bytes amount of allocated memory, all set to NULl
  in case of malloc error prints the error and exits with errno code
*/
void	*ft_malloc(size_t num_bytes)
{
	char	*allocated;
	size_t	i;

	i = 0;
	allocated = malloc(num_bytes);
	if (allocated == NULL)
	{
		perror(NULL);
		exit(MALLOC_ERROR);
	}
	while (i < num_bytes)
	{
		allocated[i] = '\0';
		i++;
	}
	return (allocated);
}

/*
  Trims starting and trailing whitespace of str
  "   exit    43  	  " produces "exit    43"
*/
char	*ft_trim_whitespace(char *str)
{
	unsigned int	start;
	size_t			end;
	char			*trimmed;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] && ft_is_space(str[start]))
		start++;
	while (str[end] && ft_is_space(str[end]))
		end--;
	trimmed = ft_substr(str, start, end - start + 1);
	return (trimmed);
}
