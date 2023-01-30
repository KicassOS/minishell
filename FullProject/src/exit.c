/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:32 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/30 06:20:14 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Frees list whose head is pointed to by lst
*/
void	ft_free_env_list(t_slist *lst)
{
	t_slist	*temp;

	while (lst)
	{
		temp = lst->next;
//		free(lst->content);
		free(lst);
		lst = temp;
	}
}

void	ft_free_commands(t_slist *commands)
{
	(void) commands;
	return ;
}

/*
  Performs all cleanup after shell execution
  Frees environment "my_env", frees input and exits with statuscode "status"
*/
void	ft_cleanup(t_data *data)
{
//	rl_clear_history();
	if (data->input_allocated)
		free(data->input);
	ft_free_commandlist(&data->commands);
	ft_free_env_list(data->env);
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
	ft_cleanup(data);
	exit(data->last_exit);
	return (EXIT_SUCCESS);
}
