/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:50:09 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/03 18:41:15 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	ft_handle_no_destination(t_list **my_env)
{
	int		result;
	char	*home_value;

	if (!ft_find_env_variable(my_env, "HOME"))
	{
		ft_putstr_fd("cd: no arguments and no HOME environment variable, aborting", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	home_value = ft_get_env_variable_value(my_env, "HOME");
	if (!home_value)
	{
		ft_putstr_fd("cd: no arguments and HOME environment variable hsa no value, aborting", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	result = chdir(home_value);
	if (result != 0)
	{
		perror(NULL);
		exit(CHDIR_ERROR);
	}
	return (EXIT_SUCCESS);
}

// add cd too many arguments
// add cd toggle between HOME and OLDPWD
char	ft_cd(t_list **my_env, char **args)
{
	int	result;
	int	arg_count;

	arg_count = ft_count_subarrays(args);
	if (arg_count > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (arg_count == 0)
		return (ft_handle_no_destination(my_env));
	result = chdir(args[0]);
	if (result != 0)
	{
		perror(NULL);
		exit(CHDIR_ERROR);
	}
	return (EXIT_SUCCESS);
}
