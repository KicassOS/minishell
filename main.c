/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:53:12 by pszleper          #+#    #+#             */
/*   Updated: 2022/08/17 19:03:39 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char				*input;

	ft_setup_signal();
	input = readline("minish> ");
	while (input && ft_strncmp(ft_trim_whitespace(input), "exit", 4) != 0)
	{
		printf("The line input was: %s\n", input);
		add_history(input);
		free(input);
		input = readline("minish> ");
	}
	rl_clear_history();
	free(input);
	return (0);
}
args = abc
args = (null)
Libft
Makefile
a.out
abc
abcde
abcdefg
abcdefgh
arma
def
f2
f3
ff
fff
ffff
fffff
fffffff
file
file1
file2
grepoutput
in
infile
libft.a
libft.h
lsoutput
main.c
main2.c
main2.o
minishell-tester
minishell.h
minishell.h.gch
outfile
pipex.h
pipex.h.gch
signal.c
signal.o
test
testttt
utils.c
utils.o
uts.c
uts.o
args = abc
args = (null)
Libft
Makefile
a.out
abc
abcde
abcdefg
abcdefgh
arma
def
f2
f3
ff
fff
ffff
fffff
fffffff
file
file1
file2
grepoutput
in
infile
libft.a
libft.h
lsoutput
main.c
main2.c
main2.o
minishell-tester
minishell.h
minishell.h.gch
outfile
pipex.h
pipex.h.gch
signal.c
signal.o
test
testttt
utils.c
utils.o
uts.c
uts.o
