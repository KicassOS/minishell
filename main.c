/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/15 14:02:05 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  copies all environment variables into a linked list
*/
t_list	*ft_copy_env(char **env, t_data *data)
{
	int		i;
	t_list	*head;

	i = 0;
	head = NULL;
	while (env[i])
	{
		ft_add_env_value(&head, env[i]);
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

static void	ft_handle_input_null(char **input, t_list **my_env)
{
	if (*input == NULL)
	{
		printf("\n");
		ft_cleanup(READLINE_ERROR, input, my_env);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*trimmed;
	t_list	*my_env;
	t_data	data;

	(void) ac;
	(void) av;
	(void) env;
	ft_setup_signal();
	while (1)
	{
		my_env = ft_copy_env(env, &data);
		input = readline("minish> ");
		ft_handle_input_null(&input, &my_env);
		trimmed = ft_trim_whitespace(input, 1);

		if (ft_strncmp(trimmed, "exit", 4) == 0)
		{
			ft_exit(&trimmed, &my_env);
		}
		if (ft_strncmp(trimmed, "export", 6) == 0)
		{
			// CHANGE THE ARG MOCKUP ARRAY TO ACTUAL PARSING
			char *args_mockup[6];
			ft_free((void **) &trimmed);
			args_mockup[0] = "TEST=HAHA";
			args_mockup[1] = "WORKING=YES";
			args_mockup[2] = "UNSET_THIS=NOPE"; // duplicate check
			args_mockup[3] = "UNSET_THIS=NOPE";
			args_mockup[4] = "TEST=MODIFIED"; // modification test
			args_mockup[5] = "\0";
			ft_export(&my_env, args_mockup);
			// ft_print_list(my_env);
		}
		else if (ft_strncmp(trimmed, "env", 3) == 0)
		{
			ft_free((void **) &trimmed);
			ft_env(&my_env);
		}
		else if (ft_strncmp(trimmed, "unset", 5) == 0)
		{
			ft_free((void **) &trimmed);
			char *args_mockup[3];
			args_mockup[0] = ft_strdup("TEST");
			args_mockup[1] = ft_strdup("WORKING");
			args_mockup[2] = ft_strdup("\0");
			ft_unset(my_env, args_mockup);
		}
		else if (ft_strncmp(trimmed, "cd", 2) == 0)
		{
			ft_free((void **)&trimmed);
			char *args_mockup[3];
			printf("Standard test with ../minitalk\n");
			args_mockup[0] = ft_strdup("../minitalk"); // normal path
			args_mockup[1] = ft_strdup("\0");
			ft_cd(&my_env, args_mockup);
			ft_pwd();
			printf("Should be equal to: /home/psz/Desktop/42/minitalk\n");
			printf("\nToo many arguments test\n");
			args_mockup[0] = ft_strdup("../subjects");
			args_mockup[1] = ft_strdup("../minishell"); // too many arguments
			args_mockup[2] = ft_strdup("\0");
			ft_cd(&my_env, args_mockup);
			ft_pwd();
			printf("Should print error and be equal to: /home/psz/Desktop/42/minitalk\n");
			printf("\nTesting valid path with tilde ~\n");
			args_mockup[0] = ft_strdup("~/Desktop/42/"); // this is going to be OLDPWD
			args_mockup[1] = ft_strdup("\0");
			ft_cd(&my_env, args_mockup);
			ft_pwd();
			printf("Should be equal to: /home/psz/Desktop/42\n");
			printf("\nTesting invalid tilde ~ path\n");
			args_mockup[0] = ft_strdup("/home/psz/~/Desktop/42");
			args_mockup[1] = ft_strdup("\0");
			ft_cd(&my_env, args_mockup);
			ft_pwd();
			printf("Should print error and be equal to /home/psz/Desktop/42\n");
			printf("\nNo arguments test!\n");
			args_mockup[0] = ft_strdup("\0");
			ft_cd(&my_env, args_mockup);
			ft_pwd(); // should be equal to HOME
			printf("Should be equal to $HOME AKA /home/psz");
			printf("\n$OLDPWD test!\n");
			args_mockup[0] = ft_strdup("-");
			ft_cd(&my_env, args_mockup);
			ft_pwd(); 
			printf("Should be equal to /home/psz/Desktop/42/ AKA OLDPWD\n");
			printf("\nTesting non-existent path\n");
			args_mockup[0] = ft_strdup("thisisannonexistentpath");
			args_mockup[1] = ft_strdup("\0");
			ft_cd(&my_env, args_mockup);
			ft_pwd(); // the ft_cd call above should return an error and not change directory
			printf("Should print error and be equal to /home/psz/Desktop/42\n");
		}
		else if (ft_strncmp(trimmed, "echo", 4) == 0)
		{
			ft_free((void **)&trimmed);
			char *args_mockup[3];
			args_mockup[0] = "Hello World";
			args_mockup[1] = "-n";
			args_mockup[2] = "\0";
			ft_echo(args_mockup[0], args_mockup[1]);
		}
		else if (ft_strncmp(trimmed, "pwd", 3) == 0)
		{
			ft_free((void **)&trimmed);
			ft_pwd();
		}
		if (ft_strlen(trimmed) > 0 && !ft_input_is_blank(trimmed) && data.has_heredoc == 0)
			add_history(trimmed);
	}
}
