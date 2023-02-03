/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:32 by pszleper          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
  Performs all cleanup after shell execution
  Frees environment "my_env", frees input and exits with statuscode "status"
*/

void	ft_cleanup(t_data *data)
{
	if (data->input_allocated)
	{
		free(data->input);
		data->input_allocated = false;
	}
	if (data->commands != NULL)
		ft_free_commandlist(&data->commands);
}

/*
  Clears the shell's history
  Frees input buffer
  Exits the shell with the status code parsed by ft_handle_exit_code
  The exit code is a single byte, so the maximum value for it is 255
  Any values above that get wrapped around
*/
int	ft_builtin_exit(t_data *data)
{
	if (data->history_allocated == true)
	{
		rl_clear_history();
		data->history_allocated = false;
	}
	ft_cleanup(data);
	exit(data->lastexitstatus);
	return (EXIT_SUCCESS);
}
