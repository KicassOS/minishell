#include "minishell.h"

int	ft_chpiping(t_list *cmdlist, t_data *data)
{
	if ((dup2(((t_cmd *)cmdlist->content)->fd[READ], STDIN_FILENO)) == -1)
		ft_failure_exit(data);
	close(((t_cmd *)cmdlist->content)->fd[READ]);
	if ((dup2(((t_cmd *)cmdlist->content)->fd[WRITE], STDOUT_FILENO)) == -1)
	{
		if (errno != EBADF)
			ft_failure_exit(data);
	}
	close(((t_cmd *)cmdlist->content)->fd[WRITE]);
	return (EXIT_SUCCESS);
}

static char	*ft_child_get_path(char *str, t_data *data)
{
	char		*ret;
	char		**paths;
	int			i;

	ret = ft_child_search_myenv(data->myenv, "PATH=");
	if (ret == NULL)
		return (NULL);
	paths = ft_split(ret + ft_strlen("PATH="), ':');
	if (paths == NULL)
		ft_failure_exit(data);
	i = 0;
	ret = NULL;
	while (paths[i] != NULL)
	{
		ft_strappend(paths[i], "/");
		ft_strappend(paths[i], str);
//		paths[i] = static_ft_append_commandname(paths[i], str);
		if (paths[i] == NULL)
			ft_failure_exit(data);
		if (access(paths[i], X_OK) != -1 && ret == NULL)
			ret = paths[i++];
		else
			free(paths[i++]);
//		i++;
	}
	free(paths);
	return (ret);
}

static void	ft_execve_child(t_list *cmdlist, t_data *data, char *path)
{
	path = ((t_cmd *)cmdlist->content)->path;
	if (!ft_strchr(path, '/'))
	{
		((t_cmd *)cmdlist->content)->path = ft_child_get_path(path, data);
		free(path);
	}
	if (((t_cmd *)cmdlist->content)->path)
	{
		if (execve(((t_cmd *)cmdlist->content)->path,
				((t_cmd *)cmdlist->content)->args, data->myenv) == -1)
		{
			if (errno == ENOENT)
				ft_printf_stderr("%s: %s %s\n", SHELL, "command not found:",
					((t_cmd *)cmdlist->content)->args[0]);
			else
				ft_printf_stderr("%s: %s %s\n", SHELL, strerror(errno),
					((t_cmd *)cmdlist->content)->args[0]);
			ft_free_data_struct_content(data);
			exit (NOTDEFINED);
		}
	}
	ft_printf_stderr("%s: %s %s\n", SHELL, "command not found:",
		((t_cmd *)cmdlist->content)->args[0]);
	ft_free_data_struct_content(data);
	exit (NOTDEFINED);
}

void	ft_child(t_list *cmdlist, t_data *data)
{
	char	*path;

	path = NULL;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, &sighandler);
	ft_fds_redirection(((t_cmd *)cmdlist->content), data);
	ft_chpiping(cmdlist, data);
	close(data->mypipe[READ]);
	close(data->mypipe[WRITE]);
	close(data->tmp_fd[0]);
	if (!((t_cmd *)cmdlist->content)->isbuiltin)
		exit(ft_execve_builtin(cmdlist, data));
	else
		ft_execve_child(cmdlist, data, path);
}
