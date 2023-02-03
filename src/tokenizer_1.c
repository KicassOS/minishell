/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:34 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_clean_spaces(t_slist **tokens)
{
	t_slist	*ptr;

	ptr = *tokens;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->content, " "))
		{
			ft_lstremovenode(tokens, ptr, &ft_del);
			ptr = *tokens;
		}
		else
			ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

static int	static_ft_handle_redirection(t_slist **tokens,
				t_data *data, t_slist **ptr)
{
	if (ft_strcmp((*ptr)->content, "<"))
	{
		if ((*ptr)->next == NULL || ft_strcmp((*ptr)->next->content, ">"))
			return (ft_exit_tokenizer(data, tokens));
		if (ft_strcmp((*ptr)->next->content, "<"))
		{
			if (ft_strappend2((char **)&(*ptr)->content, "<"))
				return (EXIT_FAILURE);
			ft_lstremovenode(tokens, (*ptr)->next, &ft_del);
		}
		*ptr = (*ptr)->next;
	}
	else
	{
		if ((*ptr)->next == NULL || ft_strcmp((*ptr)->next->content, "<"))
			return (ft_exit_tokenizer(data, tokens));
		if (ft_strcmp((*ptr)->next->content, ">"))
		{
			if (ft_strappend2(((char **)&(*ptr)->content), ">"))
				return (EXIT_FAILURE);
			ft_lstremovenode(tokens, (*ptr)->next, &ft_del);
		}
		*ptr = (*ptr)->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_clean_tokens(t_slist **tokens, t_data *data)
{
	t_slist	*ptr;

	ptr = *tokens;
	if (ft_clean_spaces(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ptr = *tokens;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->content, "|"))
		{
			if (ptr->next == NULL || ft_strcmp(ptr->next->content, "|"))
				return (ft_exit_tokenizer(data, tokens));
			((char *)ptr->content)[0] = PIPE;
		}
		else if (ft_strcmp(ptr->content, "<") || ft_strcmp(ptr->content, ">"))
		{
			if (static_ft_handle_redirection(tokens, data, &ptr))
				return (EXIT_FAILURE);
		}
		else
			ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}
