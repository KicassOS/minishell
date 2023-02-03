/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:59 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	static_ft_start_expansion(
		char **token, t_index *index, t_slist **parts, t_data *data)
{
	t_slist	*tmp;

	if ((*token)[index->i] == '$' && (*token)[index->i + 1] != '\0')
	{
		if (index->i > index->pos)
		{
			tmp = ft_lstnew(ft_substr((*token),
						index->pos, index->i - index->pos));
			if (tmp == NULL || tmp->content == NULL)
				ft_exit_expander(parts, token, &data->env);
			ft_lstadd_back(parts, tmp);
			index->pos = index->i;
		}
		ft_determine_expansion_type(token, index, parts, data);
	}
	else
		index->i = index->i + 1;
}

static void	static_ft_skip_singlequotes(char **token, int *i)
{
	*i = *i + 1;
	while ((*token)[*i] != '\'')
		*i = *i + 1;
	*i = *i + 1;
}

void	ft_create_part_list(char **token, t_index *index,
	t_slist **parts, t_data *data)
{
	t_slist	*tmp;

	while ((*token)[index->i] != '\0')
	{
		if ((*token)[index->i] == '\'')
			static_ft_skip_singlequotes(token, &index->i);
		else if ((*token)[index->i] == '\"')
		{
			index->i = index->i + 1;
			while ((*token)[index->i] != '\"' && (*token)[index->i] != '\0')
				static_ft_start_expansion(token, index, parts, data);
			index->i = index->i + 1;
		}
		else
			static_ft_start_expansion(token, index, parts, data);
	}
	if (index->i > index->pos)
	{
		tmp = ft_lstnew(ft_substr((*token), index->pos, index->i - index->pos));
		if (tmp == NULL || tmp->content == NULL)
			ft_exit_expander(parts, token, &data->env);
		ft_lstadd_back(parts, tmp);
	}
}
