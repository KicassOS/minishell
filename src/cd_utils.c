/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:53:35 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/05 21:41:30 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (s1[i] && s2[i] && s1[i] == s2[i] && i + 1 < n)
	{
		i++;
	}
	result = (unsigned char) s1[i] - (unsigned char) s2[i];
	if (result > 0)
		return (1);
	if (result < 0)
		return (-1);
	return (result);
}

void	*ft_malloc(size_t num_bytes)
{
	char	*allocated;
	size_t	i;

	i = 0;
	allocated = malloc(num_bytes);
	if (allocated == NULL)
	{
		perror(NULL);
		ft_builtin_exit(&g_data);
	}
	while (i < num_bytes)
	{
		allocated[i] = '\0';
		i++;
	}
	return (allocated);
}

int	ft_indexof_last_occurence(char *s, char c)
{
	int	pos;

	pos = ft_strlen(s);
	while (pos >= 0)
	{
		if (s[pos] == c)
			return (pos);
		pos--;
	}
	return (-1);
}

char	*ft_create_env_varstring(char *name, char *value)
{
	char	*env_value;
	int		i;
	int		j;

	env_value = ft_malloc(ft_strlen(name) + ft_strlen(value) + 2);
	i = 0;
	j = 0;
	while (i < (int) ft_strlen(name))
	{
		env_value[i] = name[i];
		i++;
	}
	env_value[i] = '=';
	i++;
	j = 0;
	while (j < (int) ft_strlen(value))
	{
		env_value[i] = value[j];
		i++;
		j++;
	}
	return (env_value);
}

void	ft_env2(t_slist **my_env)
{
	t_slist	*current;

	current = *my_env;
	while (current)
	{
		printf("[%s]\n", (char *) current->content);
		current = current->next;
	}
}
