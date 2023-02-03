/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:50:40 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_inredirect(char **command, int *y, t_cmd *simplecmd, t_data *data)
{
	if (ft_strcmp_n("\x1d\x1d", command[*y], 3) == 0)
	{
		if (command[*y + 1] == NULL)
		{
			ft_syntaxerr(data);
			return (-1);
		}
		ft_relstadd_back(&simplecmd->re,
			ft_relstnew(HERE, ft_strdup(command[*y + 1])));
		simplecmd->hasheredoc = true;
		*y = *y + 2;
	}
	else if (ft_strcmp_n("\x1d", command[*y], 2) == 0)
	{
		if (command[*y + 1] == NULL)
		{
			ft_syntaxerr(data);
			return (-1);
		}
		ft_relstadd_back(&simplecmd->re,
			ft_relstnew(IN, ft_strdup(command[*y + 1])));
		*y = *y + 2;
	}
	return (0);
}

int	ft_outredirect(char **command, int *y, t_cmd *simplecmd, t_data *data)
{
	if (ft_strcmp_n("\x1c\x1c", command[*y], 3) == 0)
	{
		if (command[*y + 1] == NULL)
		{
			ft_syntaxerr(data);
			return (-1);
		}
		ft_relstadd_back(&simplecmd->re,
			ft_relstnew(APPEND, ft_strdup(command[*y + 1])));
		*y = *y + 2;
	}
	else if (ft_strcmp_n("\x1c", command[*y], 2) == 0)
	{
		if (command[*y + 1] == NULL)
		{
			ft_syntaxerr(data);
			return (-1);
		}
		ft_relstadd_back(&simplecmd->re,
			ft_relstnew(OUT, ft_strdup(command[*y + 1])));
		*y = *y + 2;
	}
	return (0);
}

int	ft_distinguish(char **command, int *y, t_cmd *simplecmd, t_data *data)
{
	if (ft_strcmp_n("\x1d", command[*y], 2) == 0
		|| ft_strcmp_n("\x1d\x1d", command[*y], 3) == 0)
	{
		if (ft_inredirect(command, y, simplecmd, data) == -1)
			return (-1);
	}
	else if (ft_strcmp_n("\x1c", command[*y], 2) == 0
		|| ft_strcmp_n("\x1c\x1c", command[*y], 3) == 0)
	{
		if (ft_outredirect(command, y, simplecmd, data) == -1)
			return (-1);
	}
	return (0);
}

bool	ft_isredirection(char **command, int *y)
{
	if (ft_strcmp_n("\x1d", command[*y], 2) == 0
		|| ft_strcmp_n("\x1d\x1d", command[*y], 3) == 0
		|| ft_strcmp_n("\x1c", command[*y], 2) == 0
		|| ft_strcmp_n("\x1c\x1c", command[*y], 3) == 0)
		return (true);
	else
		return (false);
}

void	ft_freepipecount(char **command, char **newcmd, t_slist	*cmdtable)
{
	freedchar(&command);
	freedchar(&newcmd);
	ft_free_commandlist(&cmdtable);
}
