/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:53:10 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_subarrays(char **args)
{
	int	i;

	i = 0;
	while (args[i] && args[i][0])
		i++;
	return (i);
}

char	*ft_getcwd(void)
{
	char	*cwd_string;

	cwd_string = getcwd(NULL, 0);
	if (cwd_string == NULL)
	{
		perror(NULL);
		exit(PWD_ERROR);
	}
	return (cwd_string);
}

char	*ft_tilde_to_home(t_slist **my_env, char *path)
{
	char	*true_path;
	char	*home_path;

	if (ft_indexof_last_occurence(path, '~') > 0)
	{
		return (NULL);
	}
	if (path[0] == '~')
	{
		path++;
		home_path = ft_get_env_variable_value(my_env, "HOME");
		true_path = ft_strjoin(home_path, path);
		ft_free((void **) &home_path);
		return (true_path);
	}
	return (path);
}

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_free((void **) &args[i]);
		i++;
	}
	ft_free((void **) &args);
}

void	ft_free(void **p)
{
	free(*p);
	*p = NULL;
}
