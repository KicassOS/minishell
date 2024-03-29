/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:43 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	static_split_tokens(t_slist **tokenlist,
				int *i, int *pos, char *str)
{
	char	*tmp;
	t_slist	*node;

	if (*i > *pos)
	{
		tmp = ft_substr(str, *pos, *i - *pos);
		if (tmp == NULL)
			return (EXIT_FAILURE);
		node = ft_lstnew(tmp);
		if (node == NULL)
			return (EXIT_FAILURE);
		ft_lstadd_back(tokenlist, node);
		*pos = *i;
	}
	*i = *i + 1;
	tmp = ft_substr(str, *pos, *i - *pos);
	if (tmp == NULL)
		return (EXIT_FAILURE);
	node = ft_lstnew(tmp);
	if (node == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(tokenlist, node);
	*pos = *i;
	return (EXIT_SUCCESS);
}

static int	static_ft_create_token(t_slist **tokenlist,
				int *i, int *pos, char *str)
{
	char	*tmp;
	t_slist	*node;

	tmp = ft_substr(str, *pos, *i - *pos);
	if (tmp == NULL)
		return (EXIT_FAILURE);
	node = ft_lstnew(tmp);
	if (node == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(tokenlist, node);
	return (EXIT_SUCCESS);
}

static int	static_ft_step_through_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			return (i + 1);
		i++;
	}
	return (1);
}

void	tokenize(char *str, t_data *data, t_slist **tokens)
{
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += static_ft_step_through_quote(str + i, str[i]);
		else if (str[i] == ' ' || str[i] == '\t' || str[i] == '|'
			|| str[i] == '<' || str[i] == '>')
		{
			if (static_split_tokens(tokens, &i, &pos, str))
				ft_exit_errno(data);
		}
		else
			i++;
	}
	if (i > pos)
	{
		if (static_ft_create_token(tokens, &i, &pos, str))
			ft_exit_errno(data);
	}
}
