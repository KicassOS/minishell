/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:50:47 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**dividecmd(char **command, char **newcmd, int cmdcount)
{
	int		current;

	current = 0;
	while (current < cmdcount)
	{
		if (command[current][0] == PIPE)
			newcmd[current] = NULL;
		else
			newcmd[current] = ft_strdup(command[current]);
		current++;
	}
	newcmd[current] = NULL;
	return (newcmd);
}

int	ft_sort_cmd(char **command, t_cmd *simplecmd, int y, t_data *data)
{
	int		x;
	bool	isfirsttime;

	x = 0;
	isfirsttime = true;
	while (command[y] != NULL)
	{
		if (ft_isredirection(command, &y) == false)
		{
			if (isfirsttime == true)
			{
				isfirsttime = false;
				ft_cmdargs(command, simplecmd, &x, &y);
			}
			else
				ft_fillargs(simplecmd, command, &x, &y);
		}
		else
		{
			if (ft_distinguish(command, &y, simplecmd, data) == -1)
				return (-1);
		}
	}
	simplecmd->args[x] = NULL;
	return (0);
}

int	ft_splitdptr(char **command, t_slist **cmdtable, t_data *data)
{
	int		cmdcount;
	int		seccount;
	char	**newstr;

	cmdcount = 0;
	while (command[cmdcount] != NULL)
		cmdcount++;
	newstr = (char **)malloc((cmdcount + 1) * sizeof(char *));
	seccount = 0;
	while (seccount < cmdcount)
	{
		newstr[seccount] = ft_strdup(command[seccount]);
		seccount++;
	}
	newstr[seccount] = NULL;
	if (ft_splithelper(newstr, cmdtable, data) >= 10000)
		return (10000);
	cmdcount++;
	return (cmdcount);
}

t_slist	*ft_parser(char **command, t_data *data)
{
	int		cmdcount;
	int		pipecount;
	char	**newcmd;
	t_slist	*cmdtable;

	cmdcount = 0;
	pipecount = 0;
	newcmd = NULL;
	cmdtable = NULL;
	while (command[cmdcount] != NULL)
		cmdcount++;
	newcmd = (char **)malloc((cmdcount + 1) * sizeof(char *));
	newcmd = dividecmd(command, newcmd, cmdcount);
	freedchar(&command);
	command = NULL;
	while (pipecount < cmdcount)
		pipecount += ft_splitdptr(newcmd + pipecount, &cmdtable, data);
	parser_freedchar(&newcmd, cmdcount);
	if (pipecount > 10000)
	{
		ft_freepipecount(command, newcmd, cmdtable);
		return (NULL);
	}
	return (cmdtable);
}
