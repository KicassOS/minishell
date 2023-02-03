/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:16 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_slist	*ft_add_env_value(t_slist **my_env, char *content)
{
	t_slist	*new_node;
	char	*name;

	name = ft_extract_variable_name(content);
	if (ft_find_env_variable(my_env, name))
	{
		free(name);
		name = NULL;
		return (NULL);
	}
	new_node = ft_overwrite_env_var_value(my_env, content, content);
	new_node->next = NULL;
	free(name);
	name = NULL;
	return (new_node);
}

t_slist	*ft_copy_env(t_slist *head)
{
	int			i;
	char		*copy;
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
		{
			ft_free((void **) &copy);
		}
		i++;
	}
	return (head);
}

static int	ft_static_handlecmd(char **command, t_data *data)
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

static int	ft_static_helpermain(t_data *data)
{
	if (data->input == NULL)
		ft_builtin_exit(data);
	data->input_allocated = true;
	if (ft_strlen(data->input) > 0 && !ft_only_spacetabs(data->input) && \
		data->hasheredoc == false)
	{
		add_history(data->input);
		data->history_allocated = true;
	}
	if (ft_only_spacetabs(data->input))
	{
		free(data->input);
		return (1);
	}
	return (0);
}

int	main(void)
{
	char			**command;
	t_data			data;

	ft_setup_signal();
	ft_setup_data(&data);
	data.env = ft_copy_env(data.env);
	data.env_allocated = true;
	while (1)
	{
		data.input = readline("minish>");
		if (ft_static_helpermain(&data))
			continue ;
		command = ft_tokenizer(data.input, &data);
		if (data.input_allocated)
		{
			free(data.input);
			data.input_allocated = false;
		}
		if (command != NULL)
			if (ft_static_handlecmd(command, &data) == -1)
				continue ;
	}
	return (EXIT_SUCCESS);
}
