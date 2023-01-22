#include "minishell.h"

static void	heredoc_error(t_re *redirection, t_data *data, int i)
{
	if (errno)
	{
		if (errno != EBADF)
			ft_failure_exit(data);
	}
	else
		ft_printf_stderr("%s: warning: here-document at line %d "
			"delimeted by end-of-file (wanted `%s')\n",
			SHELL, i, redirection->file);
}

static void	stdin_terminal(t_re *redirection, t_data *data)
{
	char	*line;
	int		i;

	i = 1;
	while (true)
	{
		line = readline(HEREPROMPT);
		if (!line)
		{
			heredoc_error(redirection, data, i);
			break ;
		}
		if (ft_strcmp(line, redirection->file))
			break ;
		write(redirection->herepipe[WRITE], line, ft_strlen(line));
		write(redirection->herepipe[WRITE], "\n", 1);
		free(line);
		line = NULL;
		i++;
	}
	free(line);
}

static void	ft_heredoc(t_re *redirection, t_data *data)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	if (pipe(redirection->herepipe) == -1)
		ft_failure_exit(data);
	signal(SIGINT, &ft_sigfunc_here_doc);
	signal(SIGQUIT, SIG_IGN);
	stdin_terminal(redirection, data);
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
	close(redirection->herepipe[WRITE]);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_failure_exit(data);
}

void	ft_get_heredoc_input(t_data *data)
{
	t_list	*cmdlist;
	t_re	*tmp;

	cmdlist = data->commands;
	while (cmdlist != NULL)
	{
		tmp = ((t_cmd *)cmdlist->content)->re;
		while (tmp != NULL)
		{
			if (tmp->operator == HERE)
				ft_heredoc(tmp, data);
			tmp = tmp->next;
		}
		cmdlist = cmdlist->next;
	}
}
