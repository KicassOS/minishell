/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:35:22 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/02 16:49:39 by pszleper         ###   ########.fr       */
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
		exit(errno);
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

/*
  same as libft, but prints error message and exits on malloc error
*/
t_list	*ft_lstnew_safe(void *content)
{
	t_list	*element;

	element = ft_malloc(sizeof(t_list));
	element->content = content;
	element->next = NULL;
	return (element);
}

/*
  frees list whose head is pointed to by lst
*/
void	ft_lstfree(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = ((*lst)->next);
		ft_free((void **)&*lst);
		*lst = temp;
	}
}