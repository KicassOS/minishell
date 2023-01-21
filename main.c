/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/21 19:49:19 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Copies all environment variables into a linked list
  The linked list nodes are the same as the libft's, but with char *content
  instead of void *
*/
t_list	*ft_copy_env(char **env, t_list *head, t_data *data)
{
	int		i;
	char	*copy;

	i = 0;
	if (!head)
	{
		head = ft_env_new_node(env[i]);
		i++;
	}
	while (env[i])
	{
		copy = ft_strdup(env[i]);
		if (ft_add_env_value(&head, copy) == NULL)
			ft_free((void **) &copy);
		i++;
	}
	data->env = head;
	return (head);
}

/*
  Performs all cleanup after shell execution
  Frees environment "my_env", frees input and exits with statuscode "status"
*/
void	ft_cleanup(int status, char **input, t_list **my_env)
{
	rl_clear_history();
	ft_free((void **) input);
	ft_free_env_list(my_env);
	exit(status);
}

char	*ft_static_mainutil(char **input, t_list **my_env)
{
	char	*trimmed;

	if (*input == NULL)
	{
		printf("\n");
		ft_cleanup(READLINE_ERROR, input, my_env);
	}
	if (!(**input))
	{
		free(*input);
		printf("\n");
		trimmed = ft_malloc(1);
		trimmed[0] = '\0';
	}
	else
		trimmed = ft_trim_whitespace(*input, 1);
	return (trimmed);
}

void	ft_null_terminate_argmockup(char **args_mockup, int end)
{
	args_mockup[end - 1] = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*trimmed;
	t_list	*my_env;
	t_data	data;

	(void) ac, (void) av;
	ft_setup_signal();
	data.last_exit = EXIT_SUCCESS;
	data.has_heredoc = 0;
	my_env = NULL;
	while (1)
	{
		my_env = ft_copy_env(env, my_env, &data);
		input = readline("minish> ");
		trimmed = ft_static_mainutil(&input, &my_env);
		if (ft_strlen(trimmed) > 0 && !ft_input_is_blank(trimmed) \
			&& data.has_heredoc == 0)
			add_history(trimmed);
		ft_free((void **) &trimmed);
	}
}
