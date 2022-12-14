/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:35:22 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/14 16:29:57 by pszleper         ###   ########.fr       */
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
char	*ft_trim_whitespace(char *str, int flag)
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
	if (flag == 1)
		ft_free((void **) &str); 
	return (trimmed);
}

int	ft_indexof_last_occurence(char *s, char c)
{
	int	pos;

	pos = ft_strlen(s);
	while (pos >= 0)
	{
		if (s[pos] == c)
			return (pos);
		pos--;
	}
	return (-1);
}

char	ft_input_is_blank(char *input)
{
	size_t	i;
	size_t	j;
	char	*blanks;

	if (input == NULL)
		return (1);
	i = 0;
	blanks = BLANKS;
	while (i < ft_strlen(input))
	{
		j = 0;
		while (j < ft_strlen(blanks))
		{
			if (input[i] != blanks[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}