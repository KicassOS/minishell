/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:51:39 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_execute_builtin(t_slist *cmdlist, t_data *data)
{
	t_cmd	*cmd;

	cmd = ((t_cmd *)cmdlist->content);
	if (ft_strcmp(cmd->path, "echo") || ft_strcmp(cmd->path, "/bin/echo"))
		data->lastexitstatus = ft_echo(cmd->args);
	else if (ft_strcmp(cmd->path, "cd"))
		data->lastexitstatus = ft_cd(&data->env, cmd->args);
	else if (ft_strcmp(cmd->path, "pwd") || ft_strcmp(cmd->path, "/bin/pwd"))
		data->lastexitstatus = ft_pwd(cmd->args);
	else if (ft_strcmp(cmd->path, "export"))
	{
		if ((cmd->args != NULL) && (cmd->args[1] == NULL))
			data->lastexitstatus = ft_env(&data->env, true);
		else
			data->lastexitstatus = ft_export(&data->env, cmd->args);
	}
	else if (ft_strcmp(cmd->path, "unset"))
		data->lastexitstatus = ft_unset(&data->env, cmd->args);
	else if (ft_strcmp(cmd->path, "env") || ft_strcmp(cmd->path, "/bin/env"))
		data->lastexitstatus = ft_env(&data->env, false);
	else
		data->lastexitstatus = ft_builtin_exit(data);
	if (data->commands->next != NULL)
		ft_free_data_struct_content(data);
	return (data->lastexitstatus);
}

void	ft_dlstdel(void *content)
{
	free(content);
}

char	*ft_child_search_myenv(t_slist **my_env, char *var)
{
	t_slist	*current;

	if (*my_env == NULL)
		return (NULL);
	current = *my_env;
	while (current != NULL)
	{
		if (!ft_strcmp_n((char *)current->content, var, ft_strlen(var)))
			return ((char *)current->content);
		current = current->next;
	}
	return (NULL);
}
