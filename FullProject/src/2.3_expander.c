/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.3_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:04:36 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	static_ft_trim_nonexisting(char **str, int i)
{
	int	count;

	count = 1;
	while (ft_is_valid_char((*str)[i + count]) && (*str)[i + count] != '\0')
		count++;
	while ((*str)[i + count] != '\0')
	{
		(*str)[i] = (*str)[i + count];
		i++;
	}
	while ((*str)[i] != '\0')
	{
		(*str)[i] = '\0';
		i++;
	}
}

static int	static_ft_extract_var(int len, t_slist **list, t_slist *my_env)
{
	t_slist		*tmp;
	int			diff;
	char		*ptr;

	diff = ft_strlen((char *)my_env->content + len + 1);
	ptr = ft_substr((char *)my_env->content, len + 1, diff);
	tmp = ft_lstnew(ptr);
	if (tmp == NULL || tmp->content == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(list, tmp);
	return (EXIT_SUCCESS);
}

int	ft_expand_var(char **token, int start, t_slist **parts, t_slist **my_env)
{
	int			len;
	t_slist			*current;

	current = *my_env;
	while (current)
	{
		len = 0;
		while (((char *)current->content)[len] != '\0')
		{
			if (((char *)current->content)[len] == '='
				&& (!ft_is_valid_char((*token)[start + 1 + len])))
			{
				if (static_ft_extract_var(len, parts, current))
					ft_exit_expander(parts, token, my_env);
				return (len + 1);
			}
			else if (((char *)current->content)[len] != (*token)[start + 1 + len])
				break ;
			len++;
		}
		current = current->next;
	}
	static_ft_trim_nonexisting(token, start);
	return (0);
}
