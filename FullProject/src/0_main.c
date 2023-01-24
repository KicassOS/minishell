/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:55:20 by englot            #+#    #+#             */
/*   Updated: 2022/02/22 14:44:39 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_slist	*ft_add_env_value(t_slist **my_env, char *content)
{
	t_slist	*new_node;
	char	*name;

	name = ft_extract_variable_name(content);
	if (ft_find_env_variable(my_env, name))
	{
		ft_free((void **) &name);
		return (NULL);
	}
	new_node = ft_overwrite_env_var_value(my_env, content, content);
	ft_free((void **) &name);
	return (new_node);
}

t_slist	*ft_copy_env(t_slist *head)
{
	int		i;
	char	*copy;
	extern char	**environ;

	i = 0;
	if (!head)
	{
		head = ft_env_new_node(environ[i]);
		i++;
	}
	while (environ[i])
	{
		copy = ft_strdup(environ[i]);
		if (ft_add_env_value(&head, copy) == NULL)
			ft_free((void **) &copy);
		i++;
	}
//	data->env = head;
	return (head);
}

static void	static_ft_copy_environ(t_data *data)
{
	extern char	**environ;
	int			count;

	if (environ != NULL)
	{
		count = 0;
		while (environ[count] != NULL)
			count++;
		data->myenv = malloc((count + 1) * sizeof(char *));
		if (data->myenv == NULL)
			ft_exit_errno(data);
		count = 0;
		while (environ[count] != NULL)
		{
			data->myenv[count] = ft_strdup(environ[count]);
			if (data->myenv[count] == NULL)
				ft_exit_errno(data);
			count++;
		}
		data->myenv[count] = NULL;
	}
	else
		data->myenv = NULL;
}

static int	static_handlecmd(char **command, t_data *data)
{
	data->commands = NULL;
	if (ft_expander(command, data))
		ft_exit(data);
	ft_quoteremover(command);
	data->commands = ft_parser(command, data);
	if (data->commands == NULL || ft_emptystruct(data->commands, data))
		return (-1);
	data->mypipe[READ] = -1;
	data->mypipe[WRITE] = -1;
	ft_execute(data);
	return (0);
}

static void	static_helpermain(char *input, t_data *data)
{
	if (input == NULL)
		ft_builtin_exit(data);
	if (ft_strlen(input) > 0)
		add_history(input);
}

int	main(void)
{
//	char			*input;
	char			**command;
	t_data			data;
	struct termios	termi;
//	t_slist			*env2 = NULL;

	data.env = NULL;
	data.input = NULL;
	tcgetattr(STDIN_FILENO, &termi);
	data.lastexitstatus = EXIT_SUCCESS;
	static_ft_copy_environ(&data);
	while (1)
	{
		data.env = ft_copy_env(data.env); // assign this to data->my_env
		signal(SIGINT, &sighandler);
		signal(SIGQUIT, SIG_IGN);
		ctrlc(&termi, 0);
		data.input = readline(PROMPT);
		static_helpermain(data.input, &data);
		command = ft_tokenizer(data.input, &data);
//		free(input);
		if (command != NULL)
		{
			if (static_handlecmd(command, &data) == -1)
				continue ;
		}
	}
	ctrlc(&termi, 1);
	return (EXIT_SUCCESS);
}
