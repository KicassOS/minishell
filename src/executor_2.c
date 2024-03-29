/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:51:26 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:42:48 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**lsttoarr(t_slist **list, t_data *data)
{
	char	**array;
	int		n;
	int		i;
	t_slist	*current;

	i = 0;
	current = *list;
	n = ft_lstsize(current);
	array = malloc((n + 1) * sizeof(char *));
	if (array == NULL)
		ft_builtin_exit(data);
	while (current)
	{
		array[i] = ft_strdup(current->content);
		current = current->next;
		i++;
	}
//	current = list;
//	ft_lstclear(&current, ft_del);
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
			ret = paths[i];
		else
		{
			free(paths[i]);
		}
		i++;
	}
	free(paths);
	return (ret);
}

static void	static_ft_child_execve(t_slist *cmdlist, t_data *data, char	*tmp)
{
	char **arr = lsttoarr(&data->env, data);
	int i = 0;
	tmp = ((t_cmd *)cmdlist->content)->path;
	if (ft_strchr(tmp, '/') == NULL)
	{
		((t_cmd *)cmdlist->content)->path = static_ft_child_get_path(tmp, data);
		free(tmp);
	}
	if (((t_cmd *)cmdlist->content)->path != NULL)
	{
		if (execve(((t_cmd *)cmdlist->content)->path,
				((t_cmd *)cmdlist->content)->args, arr) == -1)
		{
			if (errno == ENOENT)
				ft_printf_stderr("%s: %s %s\n", SHELL, "command not found:",
					((t_cmd *)cmdlist->content)->args[0]);
			else
				ft_printf_stderr("%s: %s %s\n", SHELL, strerror(errno),
					((t_cmd *)cmdlist->content)->args[0]);
			ft_cleanup(data);
			while (arr[i])
			{
				free(arr[i]);
				i++;
			}
			free(arr);
//			ft_lstclear(&data->env, ft_del);
//			freedchar(&arr);
//			ft_free_commandlist(&data->env);
//			ft_free_data_struct_content(data);
			exit (NOTDEFINED);
		}
	}
	ft_printf_stderr("%s: %s %s\n", SHELL, "command not found:",
		((t_cmd *)cmdlist->content)->args[0]);
	ft_cleanup(data);
//	ft_lstclear(&data->env, ft_del);
//	ft_free_commandlist(&data->env);
//	ft_lstclear(&data->env, &static_ft_del);
	freedchar(&arr);
//	ft_free_data_struct_content(data);
	exit (NOTDEFINED);
}

int	ft_child_piping(t_slist *cmdlist, t_data *data, int *f)
{
	if ((dup2(((t_cmd *)cmdlist->content)->fd[READ], STDIN_FILENO)) == -1)
	{
		if (!f)
			ft_exit_errno(data);
		else
			ft_builtin_exit(data);
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
//	ft_cleanup(data);
//	ft_lstclear(&data->env, ft_del);
}
