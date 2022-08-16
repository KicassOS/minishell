/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/08/16 22:44:08 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char				*input;
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = ft_sigint_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &s_sigaction, NULL);
	input = readline("minish> ");
	while (input && ft_strncmp(ft_trim_whitespace(input), "exit", 4) != 0)
	{
		printf("The line input was: %s\n", input);
		add_history(input);
		free(input);
		input = readline("minish> ");
	}
	rl_clear_history();
	free(input);
	return (0);
}