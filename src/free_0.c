/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:51:52 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	static_ft_del(void *content)
{
	int		i;
	t_cmd	*cmd;
	t_re	*re;

	cmd = ((t_cmd *)content);
	free(cmd->path);
	i = 0;
	while (cmd->args != NULL && cmd->args[i] != NULL)
	{
		free(cmd->args[i]);
		cmd->args[i] = NULL;
		i++;
	}
	free(cmd->args);
	cmd->args = NULL;
	re = cmd->re;
	ft_relstclear(&re, ft_del);
	free(content);
}

void	ft_free_commandlist(t_slist **commands)
{
	if (commands == NULL)
		return ;
	ft_lstclear(commands, static_ft_del);
	return ;
}

void	freedchar(char ***dchar)
{
	int	i;

	if (*dchar == NULL)
		return ;
	i = 0;
	while ((*dchar)[i] != NULL)
	{
		free((*dchar)[i]);
		(*dchar)[i] = NULL;
		i++;
	}
	free(*dchar);
	*dchar = NULL;
}

void	ft_free_data_struct_content(t_data *data)
{
	if (data == NULL)
		return ;
	ft_free_commandlist(&data->commands);
}

void	parser_freedchar(char ***dchar, int count)
{
	int	i;

	if (*dchar == NULL)
		return ;
	i = 0;
	while (i <= count)
	{
		free((*dchar)[i]);
		(*dchar)[i] = NULL;
		i++;
	}
	free(*dchar);
	*dchar = NULL;
}
