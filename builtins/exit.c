/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:32 by pszleper          #+#    #+#             */
/*   Updated: 2022/08/19 22:26:33 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
  Clears the shell's history
  Frees input buffer
  Exits the shell with 'status' code
*/
void	ft_exit(int status, char *input)
{
	rl_clear_history();
	ft_free((void **) &input);
	exit(status);
}
