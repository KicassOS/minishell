/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:50:55 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_syntaxerr(t_data *data)
{
	data->lastexitstatus = SYNTAX;
	ft_printf_stderr("%s: syntax error near unexpected token\n", SHELL);
}

bool	ft_syntaxcheck(t_data *data)
{
	data->lastexitstatus = SYNTAX;
	ft_printf_stderr("%s: syntax error near unexpected token\n", SHELL);
	return (true);
}

void	builtinflag(t_cmd *simplecmd)
{
	if (simplecmd->args[0] == NULL)
	{
		simplecmd->isbuiltin = false;
		return ;
	}
	if (ft_strcmp_n(simplecmd->args[0], "echo", 5) == 0
		|| ft_strcmp_n(simplecmd->args[0], "cd", 3) == 0
		|| ft_strcmp_n(simplecmd->args[0], "pwd", 4) == 0
		|| ft_strcmp_n(simplecmd->args[0], "export", 7) == 0
		|| ft_strcmp_n(simplecmd->args[0], "env", 4) == 0
		|| ft_strcmp_n(simplecmd->args[0], "exit", 5) == 0
		|| ft_strcmp_n(simplecmd->args[0], "unset", 6) == 0)
		simplecmd->isbuiltin = true;
}

int	ft_countargs(char **command, t_data *data, int y, int argscount)
{
	while (command[y] != NULL)
	{
		if (ft_strcmp_n("\x1d", command[y], 2) == 0
			|| ft_strcmp_n("\x1d\x1d", command[y], 3) == 0
			|| ft_strcmp_n("\x1c", command[y], 2) == 0
			|| ft_strcmp_n("\x1c\x1c", command[y], 3) == 0)
		{
			y++;
			if (command[y] == NULL)
			{
				ft_syntaxerr(data);
				return (10000);
			}
		}
		else
		{
			argscount++;
			y++;
		}
	}
	return (argscount);
}

int	ft_splithelper(char **newstr, t_slist **cmdtable, t_data *data)
{
	t_cmd	*simplecmd;
	int		argscount;

	simplecmd = malloc(sizeof(*simplecmd));
	argscount = ft_countargs(newstr, data, 0, 0) + 1;
	if (argscount >= 10000)
		return (10000);
	simplecmd->path = NULL;
	simplecmd->args = (char **)malloc(argscount * sizeof(char *));
	if (simplecmd->args == NULL)
		return (10000);
	simplecmd->hasheredoc = false;
	simplecmd->isbuiltin = false;
	simplecmd->re = NULL;
	simplecmd->pid = 0;
	simplecmd->fd[0] = 0;
	simplecmd->fd[1] = 1;
	if (ft_sort_cmd(newstr, simplecmd, 0, data) == -1)
		return (10000);
	builtinflag(simplecmd);
	freedchar(&newstr);
	newstr = NULL;
	ft_lstadd_back(cmdtable, ft_lstnew(simplecmd));
	return (0);
}
