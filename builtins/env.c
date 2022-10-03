/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:07:40 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/02 19:12:45 by pszleper         ###   ########.fr       */
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

/*
  Returns a pointer to the t_list struct who contains content_to_find
  Returns NULL if it couldnt find the node
*/
t_list	*ft_find_env_variable(t_list **env, char *to_find)
{
	t_list	*current;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->content, to_find, ft_strlen(to_find)) != 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	ft_delete_env_node(t_list **env, char *to_find)
{
	t_list	*current;
	t_list	*before_node;
	t_list	*next_node;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->next->content, to_find, ft_strlen(to_find)) == 0)
		{
			before_node = current;
			current = current->next;
			next_node = current->next;
			ft_free((void **)&current);
			before_node->next = next_node;
			return ;
		}
		current = current->next;
	}
}
