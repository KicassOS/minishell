/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/08/20 08:16:49 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*trimmed;

	(void) ac;
	(void) av;
	(void) env;
	ft_setup_signal();
	input = readline("minish> ");
	trimmed = ft_trim_whitespace(input);
	while (input && ft_strncmp(trimmed, "exit", 4) != 0)
	{
		printf("The line input was: %s\n", input);
		add_history(input);
		ft_free((void **) &input);
		input = readline("minish> ");
		trimmed = ft_trim_whitespace(input);
	}
	ft_exit(&input, &trimmed);
	return (0);
}
