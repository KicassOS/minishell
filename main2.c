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
#include <signal.h>
#include <unistd.h>

int ft_word_count(char const *s, char c)
{
	int	word_count;
	int	i;

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

int	ft_open(char *filename, int mode, int append)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
		{
			write(STDERR, "pipex: ", 7);
			write(STDERR, filename, str_ichr(filename, 0));
			write(STDERR, ": No such file or directory\n", 28);
			return (STDIN);
		}
		return (open(filename, O_RDONLY));
	}
	else {
		if (append)
			return (open(filename, O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	}
}

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

int	ft_exec (char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (str_ichr(args[0], '/') > -1)
		path = args[0];
	else
		path = getPath(args[0], env);
//	printf("args = %s\n", args[1]);
	execve(path, args, env);
	write(STDERR, "pipex: ", 7);
	write(STDERR, cmd, str_ichr(cmd, 0));
	write(STDERR, ": command not found\n", 20);
//	exit(127);
//	if (ft_strncmp(args[1], "/dev/random", 12) == 0 || ft_strncmp(args[1], "dev/urandom", 13) == 0)
//		return 1;
	return 0;
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
}
void exit_child()
{
    exit(EXIT_FAILURE);
}

int	main (int ac, char **av, char **env)
{
	char	*input;
	int f2 = 0;
	char	**files;
	char	**inp;
	int fd_out = 1;
	int i = 0;
	int s;
	(void) ac;
	(void) av;
	int k = 0;
	int   p[2];
  	pid_t pid;
  	int   fd_in = 0;
	int	fd_in2 = 0;
	char *fs;
	int flag = 0;
	int f1 = 0;
	int ffd_out = 1;
	int append;
	char *string = NULL;
	int delim;

	input = readline("minish> ");
	while (input && ft_strncmp(ft_trim_whitespace(input), "exit", 4) != 0)
	{
		flag = 0;
		f2 = 0;
		f1 = 0;
		i = 0;
		inp = ft_split(input, '|');
//		printf("inp = %s\n", inp[0]);
		s = ft_word_count(input, '|');
//		printf("%d\n", s);
//		printf("The line input was: %s\n", input);
		add_history(input);
		if (s >= 1)
		{
			while (i < s) {
				int j = 0;
				flag = 0;
				f2 = 0;
				f1 = 0;
				append = 0;
				delim = 0;
				while ((inp[i][j] != '>' && inp[i][j] != '<') && inp[i][j])
					j++;
				char *st = malloc(sizeof(char) * j);
				st = ft_strndup(inp[i], j);
				if (inp[i][j] && (inp[i][j] == '>' || inp[i][j] == '<'))
				{
					if (inp[i][j] == '>' && inp[i][j + 1] == '>')
						append = 1;
					if (inp[i][j] == '<' && inp[i][j+1] == '<')
						delim = 1;
					flag = 1;
					if (append || delim)
						fs = malloc(sizeof(char) * (sizeof(inp[i]) - j + 1));
					else {
						fs = malloc(sizeof(char) * (sizeof(inp[i]) - j + 2));
//						printf("%s\n", inp[i] - j + 2);
					}
					fs = ft_strdup(inp[i] + j);
					files = ft_split(fs, ' ');
				}
				if (flag) {
					while (flag && k < ft_word_count(fs, ' ')) {
						if (ft_strncmp(files[k], "<", 2) == 0 || ft_strncmp(files[k], "<<", 3) == 0) {
							f1 = 1;
							k++;
							while (ft_strncmp(files[k], ">", 2) != 0 && k < ft_word_count(fs, ' ') - 1)
								k++;
							if (ft_strncmp(files[k], ">", 2) == 0)
								k--;
							if (delim) {
								fd_in2 = ft_open("test.txt", OUTFILE, append);
								while (delim) {
									string = get_next_line(0);
									if (ft_strncmp(string, "EOF", 3) == 0)
										break ;
									write(fd_in2, string, 10);
								}
								close(fd_in2);
								fd_in2 = ft_open("test.txt", INFILE, append);
							}
							else
								fd_in2 = ft_open(files[k], INFILE, append);
						}
						if (ft_strncmp(files[k], ">", 2) == 0 || ft_strncmp(files[k], ">>", 3) == 0) {
							k++;
							while (ft_strncmp(files[k], "<", 2) != 0 && k < ft_word_count(fs, ' ') - 1)
								k++;
							f2 = 1;
							if (ft_strncmp(files[k], "<", 2) == 0)
								k--;
							fd_out = ft_open(files[k], OUTFILE, append);
						}
						k++;
					}
				}
				pipe(p);
      				if ((pid = fork()) == -1)
          				exit(EXIT_FAILURE);
      				else if (pid == 0)
        			{
					if (f1) 
						dup2(fd_in2, 0);
					else
						if (ffd_out > 2) {
							dup2(ffd_out, 0);
							ffd_out = 1;
						}
						else
						dup2(fd_in, 0); //change the input according to the old one 
					if (f2) {
							dup2(fd_out, 1);
					}
					else {
						if (i != s - 1)
						dup2(p[1], 1);
					}
          				close(p[0]);

          				ft_exec(st, env);
          				exit(EXIT_FAILURE);
        			}
      				else
        			{
						waitpid(pid, NULL, 0);
          				close(p[1]);
					if (f2 && i != s - 1)
					{
						k--;
//						printf("file = %s\n", files[k]);
						ffd_out = ft_open(files[k], INFILE, append);
					}
          				fd_in = p[0]; //save the input for the next command
        			}
				i++;
				k = 0;
			}
			close(p[0]);
		}
		else
			write(STDERR, "Invalid number of arguments.\n", 29);
		free(input);
//		if (flag)
//			close(fd_in2);
		fd_in = 0;
		f2 = 0;
		input = readline("minish> ");
	}
	clear_history();
	free(input);
	return (1);
}
