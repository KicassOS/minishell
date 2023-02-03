/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:02:19 by pszleper          #+#    #+#             */
/*   Updated: 2023/02/03 15:24:46 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	ft_only_spacetabs(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

void	ft_setup_data(t_data *data)
{
	data->env = NULL;
	data->env_allocated = false;
	data->input_allocated = false;
	data->history_allocated = false;
	data->input = NULL;
	data->lastexitstatus = EXIT_SUCCESS;
	data->hasheredoc = false;
}
