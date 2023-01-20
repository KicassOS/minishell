#include "minishell.h"

static int	ft_redirect_in(t_re *redirection, t_data *data)
{
	int	fd;

	fd = open(redirection->file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_stderr("%s: %s: %s\n", SHELL,
			redirection->file, strerror(errno));
		ft_exit(data);
	}
	return (fd);
}

static int	ft_redirect_out(t_re *redirection, t_data *data)
{
	int	fd;

	fd = open(redirection->file, O_WRONLY | O_CREAT | O_TRUNC,
			RWRR);
	if (fd == -1)
	{
		ft_printf_stderr("%s: %s: %s\n", SHELL,
			redirection->file, strerror(errno));
		ft_exit(data);
	}
	return (fd);
}

static int	ft_redirect_append(t_re *redirection, t_data *data)
{
	int	fd;

	fd = open(redirection->file, O_WRONLY | O_CREAT | O_APPEND,
			RWRR);
	if (fd == -1)
	{
		ft_printf_stderr("%s: %s: %s\n", SHELL,
			redirection->file, strerror(errno));
		ft_exit(data);
	}
	return (fd);
}

int	ft_fds_redirection(t_cmd *cmd, t_data *data)
{
	t_re	*reptr;

	reptr = cmd->re;
	while (reptr != NULL)
	{
		if (reptr->operator == IN)
		{
			cmd->fd[READ] = ft_redirect_in(reptr, data);
		}
		else if (reptr->operator == OUT)
		{
			cmd->fd[WRITE] = ft_redirect_out(reptr, data);
		}
		else if (reptr->operator == APPEND)
		{
			cmd->fd[WRITE] = ft_redirect_append(reptr, data);
		}
		else
			cmd->fd[READ] = reptr->herepipe[READ];
		reptr = reptr->next;
	}
	return (EXIT_SUCCESS);
}
