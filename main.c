/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/02 17:24:48 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  copies all environment variables into my_env which is a linked list
*/
t_list	*ft_copy_env(char **env)
{
	int		i;
	t_list	*current;
	t_list	*head;

	i = 0;
	head = NULL;
	while (env[i])
	{
		current = ft_lstnew(env[i]);
		ft_lstadd_back(&head, current);
		i++;
	}
	return (head);
}
// THIS IS FOR TESTING THE ENV
// void	ft_print_list(t_list *my_env)
// {
// 	printf("\nPRINTING NEW ENVIRONMENT\n\n");
// 	while (my_env)
// 	{
// 		printf("%s\n", (char *)my_env->content);
// 		my_env = my_env->next;
// 	}
// 	return;
// }

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*trimmed;
	t_list	*my_env;

	(void) ac;
	(void) av;
	(void) env;
	my_env = ft_copy_env(env);
	ft_setup_signal();
	input = readline("minish> ");
	trimmed = ft_trim_whitespace(input);
	while (input && ft_strncmp(trimmed, "exit", 4) != 0)
	{
		if (ft_strncmp(trimmed, "export", 6) == 0)
		{
			// CHANGE THE ARG MOCKUP ARRAY TO ACTUAL PARSING
			char *args_mockup[2];
			args_mockup[0] = trimmed;
			args_mockup[1] = "\0";
			ft_export(my_env, args_mockup);
			// ft_print_list(my_env);
		}
		add_history(input);
		ft_free((void **) &input);
		input = readline("minish> ");
		trimmed = ft_trim_whitespace(input);
	}
	ft_exit(&input, &trimmed, &my_env);
	return (0);
}
