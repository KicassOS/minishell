/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:07:40 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/02 18:45:22 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_env(t_list **env)
{
	t_list	*current;

	current = *env;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

/*
  same as libft, but prints error message and exits on malloc error
*/
t_list	*ft_env_new_node(void *content)
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
void	ft_free_env_list(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = ((*lst)->next);
		ft_free((void **)&*lst);
		*lst = temp;
	}
}
