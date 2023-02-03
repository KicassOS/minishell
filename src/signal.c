/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:49:29 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	s_sigaction_ignore.sa_flags = 0;
	sigemptyset(&s_sigaction.sa_mask);
	sigemptyset(&s_sigaction_ignore.sa_mask);
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGTERM, &s_sigaction_ignore, NULL);
	sigaction(SIGQUIT, &s_sigaction_ignore, NULL);
}
