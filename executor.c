#include "minishell.h"

int	ft_execve_builtin(t_list *cmdlist, t_data *data)
{
	t_cmd	*cmd;

	cmd = ((t_cmd *)cmdlist->content);
	if (ft_strcmp(cmd->path, "echo"))
		data->lastexitstatus = ft_echo(cmd->args);
	else if (ft_strcmp(cmd->path, "cd"))
		data->lastexitstatus = ft_cd(((t_list **)data->myenv), cmd->args);
	else if (ft_strcmp(cmd->path, "pwd"))
		data->lastexitstatus = ft_pwd();
	else if (ft_strcmp(cmd->path, "export"))
	{
		if ((cmd->args != NULL) && (cmd->args[1] == NULL))
			data->lastexitstatus = ft_env((t_list **)data->myenv, true);
		else
			data->lastexitstatus = ft_export((t_list **)data->myenv, cmd->args);
	}
	else if (ft_strcmp(cmd->path, "unset"))
		data->lastexitstatus = ft_unset((t_list **)data->myenv, cmd->args);
	else if (ft_strcmp(cmd->path, "env"))
		data->lastexitstatus = ft_env((t_list **)data->myenv, false);
	else
		data->lastexitstatus = builtin_exit(data, cmd->args);
	if (data->commands->next != NULL)
		ft_free_data_struct_content(data);
	return (data->lastexitstatus);
}

static void	ft_create_children(t_data *data)
{
	t_list	*cmdlist;

	cmdlist = data->commands;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, &sighandler);
	while (cmdlist)
	{
		if (cmdlist->next)
			if (pipe(data->mypipe) == -1)
				ft_failure_exit(data);
		((t_cmd *)cmdlist->content)->fd[READ] = data->tmp_fd[0];
		((t_cmd *)cmdlist->content)->fd[WRITE] = data->mypipe[WRITE];
//		ft_piping(cmdlist, data);
		((t_cmd *)cmdlist->content)->pid = fork();
		if (((t_cmd *)cmdlist->content)->pid == -1)
			ft_exit(data);
		else if (((t_cmd *)cmdlist->content)->pid == 0)
			ft_child(cmdlist, data);
		close(data->tmp_fd[0]);
		close(data->mypipe[WRITE]);
		dup2(data->mypipe[READ], data->tmp_fd[0]);
		close(data->mypipe[READ]);
		cmdlist = cmdlist->next;
	}
}

static void	ft_execute_parent_builtin(t_data *data)
{
	data->tmp_fd[1] = dup(STDOUT_FILENO);
	if (data->tmp_fd[1] == -1)
		ft_failure_exit(data);
	ft_fds_redirection(((t_cmd *)data->commands->content), data);
	if (((t_cmd *)data->commands->content)->fd[READ] != STDIN_FILENO)
	{
		if (dup2(((t_cmd *)data->commands->content)->fd[READ],
				STDIN_FILENO) == -1)
			ft_printf_stderr("%s: %s\n", SHELL, strerror(errno));
		close(((t_cmd *)data->commands->content)->fd[READ]);
	}
	if (((t_cmd *)data->commands->content)->fd[WRITE] != STDOUT_FILENO)
	{
		if (dup2(((t_cmd *)data->commands->content)->fd[WRITE],
				STDOUT_FILENO) == -1)
			ft_printf_stderr("%s: %s\n", SHELL, strerror(errno));
		close(((t_cmd *)data->commands->content)->fd[WRITE]);
	}
	ft_execve_builtin(data->commands, data);
	dup2(data->tmp_fd[0], STDIN_FILENO);
	dup2(data->tmp_fd[1], STDOUT_FILENO);
	close(data->tmp_fd[0]);
	close(data->tmp_fd[1]);
}

static void	ft_wait(t_data *data)
{
	t_list	*ptr;
	int		count;

	count = 1;
	ptr = data->commands;
	while (ptr != NULL)
	{
		waitpid(((t_cmd *)ptr->content)->pid, &data->lastexitstatus, 0);
		ptr = ptr->next;
		count++;
	}
	if (WTERMSIG(data->lastexitstatus))
		data->lastexitstatus = WTERMSIG(data->lastexitstatus) + 128;
	else if (WIFEXITED(data->lastexitstatus))
		data->lastexitstatus = WEXITSTATUS(data->lastexitstatus);
}

void	ft_execute(t_data *data)
{
	if (!data->commands)
		ft_exit(data);
	ft_get_heredoc_input(data);
	data->tmp_fd[0] = dup(STDIN_FILENO);
	if (data->tmp_fd[0] == -1)
		ft_failure_exit(data);
	if (((t_cmd *)data->commands->content)->isbuiltin
		&& !data->commands->next)
		ft_execute_parent_builtin(data);
	else
	{
		ft_create_children(data);
		close(data->tmp_fd[0]);
		ft_wait(data);
	}
	ft_free_commandlist(&data->commands);
}
