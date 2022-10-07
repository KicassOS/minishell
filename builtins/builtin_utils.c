/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 03:49:39 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/07 03:17:30 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_tilde_to_home(t_list **my_env, char *path)
{
	char	*true_path;
	char	*home_path;

	if (ft_indexof_last_occurence(path, '~') > 0)
	{
		ft_putstr_fd("cd: invalid path (~ found in invalid position)\n", STDERR_FILENO);
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
