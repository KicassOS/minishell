/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:50:14 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	static_ft_has_closing_quote(char **str, int i)
{
	while ((*str)[i + 2] != '\0')
	{
		(*str)[i + 1] = (*str)[i + 2];
		i++;
		if ((*str)[i] == ' ')
			return (EXIT_FAILURE);
		if ((*str)[i] == '}')
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static void	static_ft_resolve_quote_case(char **token, t_index *index,
		t_data *data, t_slist **parts)
{
	if (!(static_ft_has_closing_quote(token, index->i)))
	{
		index->i = index->i + ft_expand_var(token,
				index->i, parts, &data->env) + 2;
		index->pos = index->i;
	}
	else
		ft_printf_stderr("%s: bad sunstitution\n", SHELL);
}

static int	static_ft_trim_two(char **str, int i)
{
	int	count;
	int	c;

	count = 2;
	c = 0;
	while ((*str)[i + count] != '\0')
	{
		c++;
		(*str)[i] = (*str)[i + count];
		i++;
	}
	while ((*str)[i] != '\0')
	{
		c++;
		(*str)[i] = '\0';
		i++;
	}
	return (c - 3);
}

static int	static_ft_fetchexitcode(t_slist **list,	int lastExitStatus)
{
	t_slist	*tmp;
	char	*str;

	str = ft_itoa(lastExitStatus);
	tmp = ft_lstnew(str);
	if (tmp == NULL || str == NULL)
	{
		free (str);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(list, tmp);
	return (EXIT_SUCCESS);
}

void	ft_determine_expansion_type(char **token, t_index *index,
	t_slist **parts, t_data *data)
{
	if ((*token)[index->i + 1] == '?')
	{
		if (static_ft_fetchexitcode(parts, data->lastexitstatus))
			ft_exit_expander(parts, token, &data->env);
		index->i = index->i + 2;
		index->pos = index->i;
	}
	else if (ft_isdigit((*token)[index->i + 1]))
	{
		index->i = index->i + static_ft_trim_two(token, index->i);
		index->pos = index->i;
	}
	else if (ft_is_valid_char((*token)[index->i + 1]))
	{
		index->i = index->i + ft_expand_var(token,
				index->i, parts, &data->env);
		index->pos = index->i;
	}
	else if ((*token)[index->i + 1] == '{')
		static_ft_resolve_quote_case(token, index, data, parts);
	else
		index->i = index->i + 1;
}
