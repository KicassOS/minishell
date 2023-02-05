/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:16 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/05 20:57:04 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	g_data;

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
		ft_builtin_exit(data);
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

	ft_setup_signal();
	ft_setup_data(&g_data);
	g_data.env = ft_copy_env(g_data.env);
	g_data.env_allocated = true;
	while (1)
	{
		g_data.input = readline("minish>");
		if (ft_static_helpermain(&g_data))
			continue ;
		command = ft_tokenizer(g_data.input, &g_data);
		if (g_data.input_allocated)
		{
			free(g_data.input);
			g_data.input_allocated = false;
		}
		if (command != NULL)
			if (ft_static_handlecmd(command, &g_data) == -1)
				continue ;
	}
	return (EXIT_SUCCESS);
}
