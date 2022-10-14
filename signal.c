/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:10:06 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/14 19:14:33 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_handler(int signal, siginfo_t *info, void *useless)
{
	(void) info;
	(void) useless;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_setup_signal(void)
{
	struct sigaction	s_sigaction;
	struct sigaction	s_sigaction_ignore;

	s_sigaction.sa_sigaction = ft_sigint_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction_ignore.sa_handler = SIG_IGN;
	sigemptyset(&s_sigaction.sa_mask);
	sigemptyset(&s_sigaction_ignore.sa_mask);
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGTERM, &s_sigaction_ignore, NULL);
	sigaction(SIGQUIT, &s_sigaction_ignore, NULL);
}
