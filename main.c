/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/08/16 20:43:15 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char	*input;

	input = readline("minish> ");
	while (ft_strncmp(ft_trim_whitespace(input), "exit", ft_strlen(input)) != 0)
	{
		printf("The line input was: %s\n", input);
		free(input);
		input = readline("minish> ");
	}
	free(input);
	return (0);
}