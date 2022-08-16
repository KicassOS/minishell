/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/08/16 21:35:00 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char	*input;

	input = readline("minish> ");
	while (ft_strncmp(ft_trim_whitespace(input), "exit", 4) != 0)
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