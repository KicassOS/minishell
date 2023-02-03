/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:51 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	ft_is_valid_char(const char c)
{
	if ((ft_isalpha(c)) || (ft_isdigit(c)) || (c == '_'))
		return (true);
	return (false);
}

static void	static_ft_step_through_token(char **token, t_data *data)
{
	t_index	index;
	t_slist	*parts;
	t_slist	*tmp;

	parts = NULL;
	index.i = 0;
	index.pos = 0;
	ft_create_part_list(token, &index, &parts, data);
	tmp = parts;
	while (tmp != NULL)
	{
		if (tmp != parts)
			ft_strappend2((char **)&parts->content, tmp->content);
		if (parts->content == NULL)
			ft_exit_expander(&parts, token, &data->env);
		tmp = tmp->next;
	}
	if (parts != NULL)
	{
		free(*token);
		*token = ft_strdup(parts->content);
		if (*token == NULL)
			ft_exit_expander(&parts, token, &data->env);
		ft_lstclear(&parts, ft_del);
	}
}

static bool	static_ft_needs_expansion(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && (ft_is_valid_char(str[i + 1])
				|| str[i + 1] == '?' || str[i + 1] == '{'))
			return (true);
		i++;
	}
	return (false);
}

static int	static_ft_print_token_error(void)
{
	ft_printf_stderr("%s: ERROR: expander recieved empty token list\n", SHELL);
	return (EXIT_FAILURE);
}

int	ft_expander(char **token, t_data *data)
{
	int	i;

	if (token == NULL)
		return (static_ft_print_token_error());
	i = 0;
	while (token[i] != NULL)
	{
		if (static_ft_needs_expansion(token[i]))
			static_ft_step_through_token(&token[i], data);
		i++;
	}
	return (EXIT_SUCCESS);
}
