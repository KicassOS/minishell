/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:32 by pszleper          #+#    #+#             */
/*   Updated: 2023/02/05 19:04:51 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
  Performs all cleanup after shell execution
  Frees environment "my_env", frees input
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
  Exits with either the status code given to the command or the exit code
  of the last command who ran
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

/*
  Parses the input for any possible exit code, passes it to data struct if found
  Calls ft_builtin_exit to perform all cleanup and exit with correct code
*/
int	ft_exit(t_data *data, char **args)
{
	int	parsed;
	int	arg_count;

	data->lastexitstatus = 0;
	arg_count = ft_count_subarrays(args);
	if (arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (arg_count == 2)
	{
		parsed = ft_atoi(args[1]);
		data->lastexitstatus = parsed;
	}
	ft_builtin_exit(data);
	return (EXIT_SUCCESS);
}
