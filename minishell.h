/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:54:00 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/03 03:05:48 by pszleper         ###   ########.fr       */
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

/* utils.c */
char	*ft_trim_whitespace(char *str);
void	*ft_malloc(size_t num_bytes);
t_list	*ft_env_new_node(void *content);
void	ft_free_env_list(t_list **lst);
t_list	*ft_find_env_variable(t_list **env, char *to_find);
void	ft_delete_env_node(t_list **env, char *content_to_find);

/* signal.c */
void	ft_sigint_handler(int signal, siginfo_t *info, void *useless);
void	ft_setup_signal(void);

/* builtins */
void	ft_echo(char *argument, char *flag);
void	ft_pwd(void);
void	ft_cd(char *destination);
char	ft_env(t_list **env);
void	ft_exit(char **input, char **trimmed, t_list **my_env);
char	ft_export(t_list *my_env, char **args);
char	ft_unset(t_list *my_env, char **args);

/* shared utils between builtins */
int	ft_count_subarrays(char **args);

#endif
