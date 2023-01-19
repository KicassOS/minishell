# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 20:34:13 by pszleper          #+#    #+#              #
#    Updated: 2023/01/19 05:08:01 by pszleper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME0 = minishell

HEADER = minishell.h

SRC_MINISHELL = main.c utils.c signal.c builtins/cd.c builtins/echo.c \
	builtins/env.c builtins/exit.c builtins/pwd.c builtins/export.c   \
	builtins/unset.c builtins/builtin_utils.c                         \
	builtins/environment_utils.c                                      \
	builtins/environment_utils_2.c                                    \
	builtins/environment_utils_3.c

OBJECTS_MINISHELL = $(SRC_MINISHELL:.c=.o)

OBJECTS_DEBUG = $(addprefix debug/, $(SRC_MINISHELL:.c=.o))

all: libft.a $(NAME0)

libft.a:
	make -C libft
	cp libft/libft.a .
	cp libft/libft.h .

$(NAME0): libft.a $(OBJECTS_MINISHELL)
	$(CC) $(FLAGS) $(OBJECTS_MINISHELL) libft.a -lreadline $(HEADER) -o $(NAME0)

%.o: %.c
	 $(CC) $(FLAGS) -c $< -o $@

debug/%.o: %.c
	 $(CC) $(FLAGS) -c -g $< -o $@

clean:
	rm -f */*.o

fclean: clean
	rm -f $(NAME0)
	rm -f libft.a && rm -f libft.h

re: fclean all

debug: fclean libft.a $(OBJECTS_DEBUG)
	$(CC) -g $(FLAGS) $(OBJECTS_DEBUG) libft.a -lreadline $(HEADER) -o debug/$(NAME0)

valgrind: debug
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all debug/minishell

gdb: debug
	gdb debug/minishell

.PHONY: all clean fclean re debug valgrind gdb
