/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/10/23 22:38:23 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//ENV FOR TESTING
void ft_env2(t_list **my_env)
{
	t_list *current;

	current = *my_env;
	printf("__________________________________LOGGING ENVIRONMENT__________________________\n");
	while (current)
	{
		printf("[%s]\n", (char *) current->content);
		current = current->next;
	}
	printf("__________________________________END OF ENVIRONMENT___________________________\n");
}

/*
  copies all environment variables into a linked list
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

// static void	ft_free_args_mockup(char **args_mockup, int mockup_size)
// {
// 	// Delete this once testing is all done
// 	printf("\nIN ARGS MOCKUP FREEING\n");
// 	int i;
// 	i = 0;
// 	while (i < mockup_size - 1)
// 	{
// 		printf("Freeing args_mockup[%d]\n", i);
// 		ft_free((void **) args_mockup[i]);
// 		printf("Freed!\n");
// 		i++;
// 	}
// 	printf("Freeing null-byte args_mockup[%d]\n", i);
// 	ft_free((void **) args_mockup[i]); // free the null-byte
// 	printf("Freed!\n");
// 	printf("ARGSMOCKUP FREED!\n");
// }


void	ft_null_terminate_argmockup(char **args_mockup, int end)
{
	args_mockup[end - 1] = ft_malloc(2);
	args_mockup[end - 1][0] = '\0';
	args_mockup[end - 1][1] = '\0';
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
	data.last_exit = EXIT_SUCCESS;
	data.has_heredoc = 0;
	my_env = NULL;
	while (1)
	{
		my_env = ft_copy_env(env, my_env, &data);
		input = readline("minish> ");
		trimmed = ft_static_mainutil(&input, &my_env);

		if (ft_strncmp(trimmed, "exit", 4) == 0)
		{
			ft_exit(&trimmed, &my_env);
		}
		else if (ft_strncmp(trimmed, "env", 3) == 0)
		{
			ft_env(&my_env);
		}
		if (ft_strncmp(trimmed, "test_suite", 10) == 0) // delete this whole code block once testing is done
		{
			printf("----------Executing builtins test suite----------\n");
			// printf("----------pwd----------\n");
			// ft_pwd();
			// printf("This should've simply displayed the correct current working directory");


			// printf("\n\n----------env----------\n");
			// ft_env(&my_env); // that's env testing done
			// printf("\nThis should've displayed the environment\n");


			printf("\n----------export----------\n");
			char **export_args_mockup_1;
			printf("Testing export with no arguments\n");
			export_args_mockup_1 = ft_malloc(sizeof(char *) * 1);
			ft_null_terminate_argmockup(export_args_mockup_1, 1);
			ft_export(&my_env, export_args_mockup_1);
			printf("This should've printed the environment declarations\n\n");

			char **export_args_mockup_2;
			export_args_mockup_2 = ft_malloc(sizeof(char *) * 6);
			export_args_mockup_2[0] = ft_strdup("TEST=HAHA");
			export_args_mockup_2[1] = ft_strdup("WORKING=YES");
			export_args_mockup_2[2] = ft_strdup("UNSET_THIS=NOPE"); // duplicate check
			export_args_mockup_2[3] = ft_strdup("UNSET_THIS=NOPE");
			export_args_mockup_2[4] = ft_strdup("TEST=MODIFIED"); // modification test
			ft_null_terminate_argmockup(export_args_mockup_2, 6);
			ft_export(&my_env, export_args_mockup_2);
			ft_env(&my_env);
			printf("\nThis should've displayed the standard environment, with TEST=MODIFIED, WORKING=YES, UNSET_THIS=NOPE without duplicates\n");

			char **args_mockup_unset;
			printf("\n----------unset----------\n");
			args_mockup_unset = ft_malloc(sizeof(char *) * 3);
			args_mockup_unset[0] = ft_strdup("TEST");
			args_mockup_unset[1] = ft_strdup("WORKING");
			ft_null_terminate_argmockup(args_mockup_unset, 3);
			ft_unset(&my_env, args_mockup_unset);
			ft_env(&my_env);
			printf("\nThis should've displayed the environment WITHOUT TEST and WORKING because it removed them\n");

			char **args_mockup_cd_1;
			printf("\n----------cd----------\n");
			printf("Standard test with ../minitalk\n");
			args_mockup_cd_1 = malloc(sizeof(char *) * 2);
			args_mockup_cd_1[0] = ft_strdup("../minitalk"); // normal path
			ft_null_terminate_argmockup(args_mockup_cd_1, 2);
			ft_cd(&my_env, args_mockup_cd_1);
			ft_pwd();
			printf("Should be equal to: /home/psz/Desktop/42/minitalk\n");

			char **args_mockup_cd_2;
			printf("\nToo many arguments test\n");
			args_mockup_cd_2 = malloc(sizeof(char *) * 3);
			args_mockup_cd_2[0] = ft_strdup("../subjects");
			args_mockup_cd_2[1] = ft_strdup("../minishell"); // too many arguments
			ft_null_terminate_argmockup(args_mockup_cd_2, 3);
			ft_cd(&my_env, args_mockup_cd_2);
			ft_pwd();
			printf("Should print error and be equal to: /home/psz/Desktop/42/minitalk\n");

			char **args_mockup_cd_3;
			printf("\nTesting valid path with tilde ~\n");
			args_mockup_cd_3 = malloc(sizeof(char *) * 2);
			args_mockup_cd_3[0] = ft_strdup("~/Desktop/42/"); // this is going to be OLDPWD
			ft_null_terminate_argmockup(args_mockup_cd_3, 2);
			ft_cd(&my_env, args_mockup_cd_3);
			ft_pwd();
			printf("Should be equal to: /home/psz/Desktop/42\n");

			char **args_mockup_cd_4;
			printf("\nTesting invalid tilde ~ path\n");
			args_mockup_cd_4 = malloc(sizeof(char *) * 2);
			args_mockup_cd_4[0] = ft_strdup("/home/psz/~/Desktop/42");
			ft_null_terminate_argmockup(args_mockup_cd_4, 2);
			ft_cd(&my_env, args_mockup_cd_4);
			ft_pwd();
			printf("Should print error and be equal to /home/psz/Desktop/42\n");

			char **args_mockup_cd_5;
			printf("\nNo arguments test!\n");
			args_mockup_cd_5 = malloc(sizeof(char *) * 1);
			ft_null_terminate_argmockup(args_mockup_cd_5, 1);
			ft_cd(&my_env, args_mockup_cd_5);
			ft_pwd(); // should be equal to HOME
			printf("Should be equal to $HOME AKA /home/psz\n");

			char **args_mockup_cd_6;
			printf("\n$OLDPWD test!\n");
			args_mockup_cd_6 = malloc(sizeof(char *) * 2);
			args_mockup_cd_6[0] = ft_strdup("-");
			ft_null_terminate_argmockup(args_mockup_cd_6, 2);
			ft_cd(&my_env, args_mockup_cd_6);
			ft_pwd(); 
			printf("Should be equal to /home/psz/Desktop/42/ AKA OLDPWD\n");

			char **args_mockup_cd_7;
			printf("\nTesting non-existent path\n");
			args_mockup_cd_7 = malloc(sizeof(char *) * 2);
			args_mockup_cd_7[0] = ft_strdup("thisisannonexistentpath");
			ft_null_terminate_argmockup(args_mockup_cd_7, 2);
			ft_cd(&my_env, args_mockup_cd_7);
			ft_pwd(); // the ft_cd call above should return an error and not change directory
			printf("Should print error and be equal to /home/psz/Desktop/42\n");


			char **args_mockup_echo_1;
			printf("\n----------echo----------\n");
			printf("Testing -n flag\n");
			args_mockup_echo_1 = malloc(sizeof(char *) * 3);
			args_mockup_echo_1[0] = ft_strdup("Hello World");
			args_mockup_echo_1[1] = ft_strdup("-n");
			ft_null_terminate_argmockup(args_mockup_echo_1, 3);
			ft_echo(args_mockup_echo_1);
			printf("$");
			printf("\nThis should've printed Hello World WITHOUT a newline (the dollar is the end of the string\n");

			char **args_mockup_echo_2;
			printf("\nTesting WITHOUT the -n flag\n");
			args_mockup_echo_2 = malloc(sizeof(char *) * 3);
			args_mockup_echo_2[0] = ft_strdup("Hello World");
			args_mockup_echo_2[1] = ft_malloc(1);
			args_mockup_echo_2[1][0] = '\0';
			ft_null_terminate_argmockup(args_mockup_echo_2, 3);
			ft_echo(args_mockup_echo_2);
			printf("$");
			printf("\nThis should've printed Hello World WITH a newline (the dollar is the end of the string\n");
		}
	if (ft_strlen(trimmed) > 0 && !ft_input_is_blank(trimmed) && data.has_heredoc == 0)
			add_history(trimmed);
	ft_free((void **) &trimmed);
	}
}
