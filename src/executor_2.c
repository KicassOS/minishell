/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:51:26 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**lsttoarr(t_slist **list)
{
	char	**array;
	t_slist	*current;
	int		len;
	int		n;
	int		i;

	current = *list;
	i = 0;
	n = ft_lstsize(current);
	array = malloc((n + 1) * sizeof(char *));
	while (current)
	{
		len = strlen((char *)current->content) + 1;
		array[i] = malloc(len * sizeof(char));
		ft_strcpy_l(array[i], (char *)current->content, len);
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

static char	*static_ft_child_get_path(char *str, t_data *data)
{
	char		*ret;
	char		**paths;
	int			i;

	ret = ft_child_search_myenv(&data->env, "PATH=");
	if (ret == NULL)
		return (NULL);
	paths = ft_split(ret + ft_strlen("PATH="), ':');
	if (paths == NULL)
		ft_exit_errno(data);
	i = 0;
	ret = NULL;
	while (paths[i] != NULL)
	{
		paths[i] = ft_strappend(paths[i], "/");
		paths[i] = ft_strappend(paths[i], str);
		if (paths[i] == NULL)
			ft_exit_errno(data);
		if (access(paths[i], X_OK) != -1 && ret == NULL)
			ret = paths[i++];
		else
			free(paths[i++]);
	}
	free(paths);
	return (ret);
}

static void	static_ft_child_execve(t_slist *cmdlist, t_data *data, char	*tmp)
{
	tmp = ((t_cmd *)cmdlist->content)->path;
	if (ft_strchr(tmp, '/') == NULL)
	{
		((t_cmd *)cmdlist->content)->path = static_ft_child_get_path(tmp, data);
		free(tmp);
	}
	if (((t_cmd *)cmdlist->content)->path != NULL)
	{
		if (execve(((t_cmd *)cmdlist->content)->path,
				((t_cmd *)cmdlist->content)->args, lsttoarr(&data->env)) == -1)
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

int	ft_child_piping(t_slist *cmdlist, t_data *data, int *f)
{
	if ((dup2(((t_cmd *)cmdlist->content)->fd[READ], STDIN_FILENO)) == -1)
	{
		if (!f)
			ft_exit_errno(data);
		else
			ft_exit(data);
	}
	if (((t_cmd *)cmdlist->content)->fd[READ] != -1)
		close(((t_cmd *)cmdlist->content)->fd[READ]);
	if ((dup2(((t_cmd *)cmdlist->content)->fd[WRITE], STDOUT_FILENO)) == -1)
	{
		if (errno != EBADF)
			ft_exit_errno(data);
	}
	if (((t_cmd *)cmdlist->content)->fd[WRITE] != -1)
		close(((t_cmd *)cmdlist->content)->fd[WRITE]);
	return (EXIT_SUCCESS);
}

void	ft_childprocess(t_slist *cmdlist, t_data *data, int *f)
{
	char	*tmppath;

	tmppath = NULL;
	ft_child_redirect_std_fds(((t_cmd *)cmdlist->content), data, f);
	ft_child_piping(cmdlist, data, f);
	if (data->mypipe[READ] != -1 && data->mypipe[WRITE] != -1
		&& data->tmp_fd[0] != -1)
	{
		close(data->mypipe[READ]);
		close(data->mypipe[WRITE]);
		close(data->tmp_fd[0]);
	}
	if (((t_cmd *)cmdlist->content)->isbuiltin)
		exit(ft_execute_builtin(cmdlist, data));
	else
		static_ft_child_execve(cmdlist, data, tmppath);
}
