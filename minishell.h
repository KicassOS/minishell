/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:54:00 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/06 23:24:59 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <unistd.h>
# include "libft.h"

# define MALLOC_ERROR 5
# define CHDIR_ERROR 6
# define PWD_ERROR 7

/* utils.c */
char	*ft_trim_whitespace(char *str);
void	*ft_malloc(size_t num_bytes);

/* environment_utils.c */
t_list	*ft_env_new_node(void *content);
void	ft_free_env_list(t_list **lst);
t_list	*ft_find_env_variable(t_list **env, char *to_find);
void	ft_delete_env_node(t_list **env, char *content_to_find);
char	*ft_get_env_variable_value(t_list **my_env, char *needle);

/* environment_utils_2.c */
char	ft_is_valid_env_variable(char *variable);
char	*ft_extract_variable_value(char *content);
char	*ft_extract_variable_name(char *content);
t_list	*ft_overwrite_env_var_value(t_list **my_env, char *oldval, char *newval);
t_list	*ft_modify_env_var_value(t_list **my_env, char *name, char *value);

/* environment_utils_3.c */
char	*ft_create_env_value(char *name, char *value);

/* signal.c */
void	ft_sigint_handler(int signal, siginfo_t *info, void *useless);
void	ft_setup_signal(void);

/* builtins */
void	ft_echo(char *argument, char *flag);
void	ft_pwd(void);
char	ft_cd(t_list **my_env, char **args);
char	ft_env(t_list **env);
void	ft_exit(char **input, char **trimmed, t_list **my_env);
char	ft_export(t_list **my_env, char **args);
char	ft_unset(t_list *my_env, char **args);

/* builtin_utils.c */
int	ft_count_subarrays(char **args);
char	*ft_getcwd(void);

#endif
