/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:20:32 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/14 16:00:52 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
  This function scans the code next to exit and performs ft_atoi on it
  to get the value of the code as an int and pass it to ft_exit
*/
int	ft_handle_exit_code(char *input)
{
	int		i;
	int		j;
	int		statuscode;
	char	*statuscode_str;

	i = 0;
	j = 0;
	statuscode = 0;
	while (input[i])
	{
		while (input[i] && !ft_isdigit(input[i]))
			i++;
		j = i;
		while (input[j] && ft_isdigit(input[j]))
			j++;
		break ;
	}
	statuscode_str = ft_substr(input, i, j - i + 1);
	statuscode = ft_atoi(statuscode_str);
	ft_free((void **) &statuscode_str);
	return (statuscode);
}

/*
  Frees list whose head is pointed to by lst
*/
void	ft_free_env_list(t_list **lst)
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = ((*lst)->next);
		// ft_free((void **) &lst->content) UNCOMMENT ONCE CONTENT IS MALLOC'D
		ft_free((void **) lst);
		*lst = temp;
	}
}

/*
  Clears the shell's history
  Frees input buffer
  Exits the shell with the status code parsed by ft_handle_exit_code
  The exit code is a single byte, so the maximum value for it is 255
  Any values above that get wrapped around
*/
void	ft_exit(char **input, t_list **my_env)
{
	int	status_code;

	status_code = ft_handle_exit_code(*input);
	ft_cleanup(status_code, input, my_env);
}
