/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:51:32 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	static_ft_child_redirect_in(t_re *redirection, t_data *data, int *f)
{
	int	fd;

	fd = open(redirection->file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_stderr("%s: %s: %s\n", SHELL,
			redirection->file, strerror(errno));
		*f += 1;
		ft_builtin_exit(data);
	}
	return (fd);
}

static int	static_ft_child_redirect_out(t_re *redirection,
				t_data *data, int *f)
{
	int	fd;

	fd = open(redirection->file, O_WRONLY | O_CREAT | O_TRUNC,
			RWRR);
	if (fd == -1)
	{
		ft_printf_stderr("%s: %s: %s\n", SHELL,
			redirection->file, strerror(errno));
		*f += 1;
		ft_builtin_exit(data);
	}
	return (fd);
}

static int	static_ft_child_redirect_append(t_re *redirection,
				t_data *data, int *f)
{
	int	fd;

	fd = open(redirection->file, O_WRONLY | O_CREAT | O_APPEND,
			RWRR);
	if (fd == -1)
	{
		ft_printf_stderr("%s: %s: %s\n", SHELL,
			redirection->file, strerror(errno));
		*f += 1;
		ft_builtin_exit(data);
	}
	return (fd);
}

int	ft_child_redirect_std_fds(t_cmd *cmd, t_data *data, int *f)
{
	t_re	*reptr;

	reptr = cmd->re;
	while (reptr != NULL)
	{
		if (reptr->operator == IN)
		{
			cmd->fd[READ] = static_ft_child_redirect_in(reptr, data, f);
		}
		else if (reptr->operator == OUT)
		{
			cmd->fd[WRITE] = static_ft_child_redirect_out(reptr, data, f);
		}
		else if (reptr->operator == APPEND)
		{
			cmd->fd[WRITE] = static_ft_child_redirect_append(reptr, data, f);
		}
		else
			cmd->fd[READ] = reptr->herepipe[READ];
		reptr = reptr->next;
	}
	return (EXIT_SUCCESS);
}
