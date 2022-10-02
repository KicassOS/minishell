/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:54:00 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/02 16:52:01 by pszleper         ###   ########.fr       */
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
t_list	*ft_lstnew_safe(void *content);
void	ft_lstfree(t_list **lst);


/* signal.c */
void	ft_sigint_handler(int signal, siginfo_t *info, void *useless);
void	ft_setup_signal(void);

/* builtins */
void	ft_echo(char *argument, char *flag);
void	ft_pwd(void);
void	ft_cd(char *destination);
void	ft_env(char **env);
void	ft_exit(char **input, char **trimmed, t_list **my_env);
char	ft_export(t_list *my_env, char **args);

#endif
