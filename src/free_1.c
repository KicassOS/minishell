/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:52:09 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:42:50 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exit_tokenizer(t_data *data, t_slist **tokens)
{
	ft_syntaxerr(data);
	ft_lstclear(tokens, &ft_del);
	return (EXIT_FAILURE);
}

void	ft_exit_expander(t_slist **slist, char **token, t_slist **my_env)
{
	ft_printf_stderr("%s: Error: %s\n", SHELL, strerror(errno));
	ft_lstclear(slist, ft_del);
	free(*token);
	ft_lstclear(my_env, ft_del);
	exit (EXIT_FAILURE);
}

void	ft_exit_errno(t_data *data)
{
	ft_printf_stderr("%s: %s\n", SHELL, strerror(errno));
	ft_builtin_exit(data);
}
