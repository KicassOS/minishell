/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:50:09 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/23 21:54:39 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
  sets the $PWD and $OLDPWD environment variables after cd has run
*/
static char	ft_set_cd_env_vars(t_list **my_env, char **oldpwd_value)
{
	char	*pwd_value;

	pwd_value = ft_getcwd();
	ft_modify_env_var_value(my_env, ft_strdup("PWD"), pwd_value);
	ft_modify_env_var_value(my_env, ft_strdup("OLDPWD"), *oldpwd_value);
	return (EXIT_SUCCESS);
}

/*
  Changes the directory, converting any tildes it finds to $HOME
*/
static int	ft_true_path_chdir(t_list **my_env, char **args, char *origin_pwd)
{
	char	*true_path;
	int		result;

	true_path = ft_tilde_to_home(my_env, args[0]);
	if (!true_path)
	{
		ft_putstr_fd("cd: Invalid path\n", STDERR_FILENO);
		free(args[0]);
		ft_free((void **) &origin_pwd);
		return (CHDIR_ERROR);
	}
	result = chdir(true_path);
	if (result != 0)
	{
		ft_free((void **) &origin_pwd);
		ft_free((void **) &true_path);
		perror("cd");
		return (CHDIR_ERROR);
	}
	ft_free((void **) &origin_pwd);
	ft_free((void **) &true_path);
	return(ft_set_cd_env_vars(my_env, &origin_pwd));
}

/*
  Gets called when cd has no arguments, and changes directory to $HOME
*/
static char	ft_handle_no_destination(t_list **my_env, char **oldpwd)
{
	int		result;
	char	*home_value;

	home_value = ft_get_env_variable_value(my_env, "HOME");
	if (home_value == NULL)
	{
		ft_putstr_fd("cd: no arguments and no HOME ", STDERR_FILENO);
		ft_putstr_fd("environment variable, aborting\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	result = chdir(home_value);
	if (result != 0)
	{
		perror("cd");
		ft_free((void **) &home_value);
		return (CHDIR_ERROR);
	}
	ft_free((void **) &home_value);
	ft_set_cd_env_vars(my_env, oldpwd);
	return (EXIT_SUCCESS);
}

/*
  Gets called when '-' is passed to ft_cd, and changes directory to $OLDPWD
*/
static char	ft_goto_oldpwd(t_list **my_env)
{
	char	*oldpwd_value;
	char	*origin_pwd;
	int		result;

	oldpwd_value = ft_get_env_variable_value(my_env, "OLDPWD");
	if (oldpwd_value == NULL)
	{
		ft_putstr_fd("minish: cd: OLDPWD not set\n", 2);
		return (CHDIR_ERROR);
	}
	origin_pwd = ft_getcwd();
	result = chdir(oldpwd_value);
	if (result != 0)
	{
		ft_free((void **) &oldpwd_value);
		ft_free((void **) &origin_pwd);
		perror("cd");
		return (CHDIR_ERROR);
	}
	ft_free((void **) &oldpwd_value);
	ft_free((void **) &origin_pwd);
	return (EXIT_SUCCESS);
}

char	ft_cd(t_list **my_env, char **args)
{
	int		arg_count;
	char	*origin_pwd;

	arg_count = ft_count_subarrays(args);
	if (arg_count > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	origin_pwd = ft_getcwd();
	if (arg_count == 0)
		return (ft_handle_no_destination(my_env, &origin_pwd));
	if (ft_strncmp(args[0], "-", ft_strlen(args[0])) == 0)
	{
		ft_free((void **) &args[0]);
		ft_free((void **) &origin_pwd);
		return (ft_goto_oldpwd(my_env));
	}
	return (ft_true_path_chdir(my_env, args, origin_pwd));
}
