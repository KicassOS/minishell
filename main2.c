/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/08/16 22:07:54 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "pipex.h"
#include "libft.h"
static size_t	ft_word_count(char const *s, char c)
{
	size_t	word_count;
	size_t	i;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			word_count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (word_count);
}

/*int	ft_open(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
		{
			write(STDERR, "pipex: ", 7);
			write(STDERR, filename, str_ichr(filename, 0));
			write(STDERR, ": Noooo such file or directory\n", 28);
			return (STDIN);
		}
		return (open(filename, O_RDONLY));
	}
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}*/

char	*getPath (char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && str_ncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && str_ichr(path, ':') > -1)
	{
		dir = str_ndup(path, str_ichr(path, ':'));
		bin = path_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_ichr(path, ':') + 1;
	}
	return (cmd);
}

void	ft_exec (char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (str_ichr(args[0], '/') > -1)
		path = args[0];
	else
		path = getPath(args[0], env);
	execve(path, args, env);
	write(STDERR, "pipex: ", 7);
	write(STDERR, cmd, str_ichr(cmd, 0));
	write(STDERR, ": command not found\n", 20);
	exit(127);
}

void	redir (char *cmd, char **env, int i, int s)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (i != s - 1)
			if (dup2(pipefd[1], 1) < 0)
				exit(EXIT_FAILURE);
		if (i != 0)
			if (dup2(pipefd[0], 0) < 0)
				exit(EXIT_FAILURE);

		close(pipefd[0]);
		close(pipefd[1]);

		ft_exec(cmd, env);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
/*	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		if (fd1 == STDIN)
			exit(1);
		else
			ft_exec(cmd, env);
	}*/
}

int	main (int ac, char **av, char **env)
{
	char	*input;
	char	**inp;
//	int fd1, fd2;
	int i = 0;
	int s;
	(void) ac;
	(void) av;
int   p[2];
  pid_t pid;
  int   fd_in = 0;

	input = readline("minish> ");
	while (input && ft_strncmp(ft_trim_whitespace(input), "exit", 4) != 0)
	{
		i = 0;
		inp = ft_split(input, '|');
		printf("inp = %s\n", inp[0]);
		s = ft_word_count(input, '|');
		printf("%d\n", s);
		printf("The line input was: %s\n", input);
		add_history(input);
	if (s >= 1)
	{
//		fd1 = ft_open(inp[0], INFILE);
//		fd2 = ft_open(inp[s - 1], OUTFILE);
//		dup2(fd1, STDIN);
//		dup2(fd2, STDOUT);
//		redir(inp[0], env, 0, s);
		while (i < s) {
//
//
//
			pipe(p);
      			if ((pid = fork()) == -1)
        		{
          			exit(EXIT_FAILURE);
        		}
      			else if (pid == 0)
        		{
          			dup2(fd_in, 0); //change the input according to the old one 
          			if (i != s - 1)
            				dup2(p[1], 1);
          			close(p[0]);
          			ft_exec(inp[i], env);
          			exit(EXIT_FAILURE);
        		}
      			else
        		{
          			wait(NULL);
          			close(p[1]);
          			fd_in = p[0]; //save the input for the next command
          		
//			redir(inp[i], env, i, s);	
//			i++;
        		}
//
//
//			redir(inp[i], env, i, s);
			i++;
		}
//		if (s != 1)
//			ft_exec(inp[i], env);
	}
	else
		write(STDERR, "Invalid number of arguments.\n", 29);
	free(input);
	input = readline("minish> ");
	}
	clear_history();
	free(input);
	return (1);
}
