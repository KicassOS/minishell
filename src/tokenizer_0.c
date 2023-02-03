/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:49:25 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 18:06:14 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	check_unclosed_quotes(char *str, int *i, char quote, t_data *data)
{
	*i += 1;
	while (str[*i] && str[*i] != quote)
		*i += 1;
	if (!str[*i])
	{
		data->lastexitstatus = SYNTAX;
		ft_printf_stderr("%s: Error: unclosed quotes\n", SHELL);
		return (true);
	}
	return (false);
}

static char	**static_ft_change_redirection_operator_chars(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		if (ft_strcmp(array[i], "<"))
			array[i][0] = SMALLER;
		else if (ft_strcmp(array[i], ">"))
			array[i][0] = BIGGER;
		else if (ft_strcmp(array[i], "<<"))
		{
			array[i][0] = SMALLER;
			array[i][1] = SMALLER;
		}
		else if (ft_strcmp(array[i], ">>"))
		{
			array[i][0] = BIGGER;
			array[i][1] = BIGGER;
		}
		i++;
	}
	return (array);
}

static char	**static_ft_create_command_array(t_slist **tokens, t_data *data)
{
	int		count;
	char	**array;
	t_slist	*tmp;
	int		i;

	count = ft_lstsize(*tokens);
	array = malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		ft_exit_errno(data);
	tmp = *tokens;
	i = 0;
	while (tmp != NULL)
	{
		array[i] = ft_strdup(tmp->content);
		if (array[i] == NULL)
			ft_exit_errno(data);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	ft_lstclear(tokens, &ft_del);
	return (static_ft_change_redirection_operator_chars(array));
}

int	check_syntax_error(t_slist *ptr, t_data *data, t_slist **tokens)
{
	if (ft_strcmp(ptr->content, "<<"))
	{
		if (ptr->next == NULL || ft_strcmp(ptr->next->content, "<")
			|| ft_strcmp(ptr->next->content, ">"))
			return (ft_exit_tokenizer(data, tokens));
	}
	if (ft_strcmp(ptr->content, ">>"))
	{
		if (ptr->next == NULL || ft_strcmp(ptr->next->content, "<")
			|| ft_strcmp(ptr->next->content, ">"))
			return (ft_exit_tokenizer(data, tokens));
	}
	return (EXIT_SUCCESS);
}

char	**ft_tokenizer(char *str, t_data *data)
{
	t_slist	*tokens;
	t_slist	*ptr;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			if (check_unclosed_quotes(str, &i, str[i], data))
				return (NULL);
		i++;
	}
	tokens = NULL;
	tokenize(str, data, &tokens);
	if (ft_clean_tokens(&tokens, data))
		return (NULL);
	ptr = tokens;
	while (ptr != NULL)
	{
		if (check_syntax_error(ptr, data, &tokens) != EXIT_SUCCESS)
			return (NULL);
		ptr = ptr->next;
	}
	return (static_ft_create_command_array(&tokens, data));
}
