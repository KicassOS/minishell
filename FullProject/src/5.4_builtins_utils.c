/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.4_builtins_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:06:17 by englot            #+#    #+#             */
/*   Updated: 2022/02/21 21:11:35 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_myenv_index(char **myenv, char *var)
{
	int			i;

	if (myenv == NULL)
		return (ERROR);
	i = 0;
	while (myenv[i] != NULL)
	{
		if (!ft_strcmp_n(myenv[i], var, ft_strlen(var)))
			return (i);
		i++;
	}
	return (ERROR);
}

void	ft_dlstdel(void *content)
{
	free(content);
}

int	ft_exchange_envvar(int i, char **myenv, char *replacement)
{
	char	*tmp;

	tmp = ft_strdup(replacement);
	if (tmp == NULL)
		return (ft_errormessage(strerror(errno)));
	else
	{
		free(myenv[i]);
		myenv[i] = tmp;
	}
	return (EXIT_SUCCESS);
}

char	*ft_child_search_myenv(char **myenv, char *var)
{
	int			i;

	if (myenv == NULL)
		return (NULL);
	i = 0;
	while (myenv[i] != NULL)
	{
		if (!ft_strcmp_n(myenv[i], var, ft_strlen(var)))
			return (myenv[i]);
		i++;
	}
	return (NULL);
}
