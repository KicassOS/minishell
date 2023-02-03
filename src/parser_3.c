/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:51:02 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_args(t_cmd *simplecmd, char **command, int *x, int *y)
{
	int	index;

	index = 0;
	simplecmd->path = ft_strdup(command[*y]);
	index = ft_strindexrev(command[*y], '/') + 1;
	simplecmd->args[*x] = ft_substr(command[*y], index,
			(ft_strlen(command[*y]) - index));
	(*y)++;
	(*x)++;
}

void	ft_pathcmd(t_cmd *simplecmd, char **command, int *x, int *y)
{
	simplecmd->path = ft_strdup(command[*y]);
	simplecmd->args[*x] = ft_strdup(command[*y]);
	(*y)++;
	(*x)++;
}

void	ft_cmdargs(char **command, t_cmd *simplecmd, int *x, int *y)
{
	if (ft_strindex(command[*y], '/') != -1)
		ft_args(simplecmd, command, x, y);
	else
		ft_pathcmd(simplecmd, command, x, y);
}

void	ft_fillargs(t_cmd *simplecmd, char **command, int *x, int *y)
{
	simplecmd->args[*x] = ft_strdup(command[*y]);
	(*y)++;
	(*x)++;
}

bool	ft_emptystruct(t_slist *cmdtable, t_data *data)
{
	t_slist	*temp;

	temp = cmdtable;
	if (temp == NULL)
		return (true);
	while (temp != NULL)
	{
		if (((t_cmd *)temp->content)->path == NULL
			&& ((t_cmd *)temp->content)->args[0] == NULL
			&& ((t_cmd *)temp->content)->re == NULL)
			return (ft_syntaxcheck(data));
		temp = temp->next;
	}
	return (false);
}
