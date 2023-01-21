# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 20:34:13 by pszleper          #+#    #+#              #
#    Updated: 2023/01/21 16:18:17 by pszleper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME0 = minishell

HEADER = minishell.h

LIBFT = libft/libft.a

SRC_MINISHELL = main.c utils.c signal.c builtins/cd.c builtins/echo.c \
	builtins/env.c builtins/exit.c builtins/pwd.c builtins/export.c   \
	builtins/unset.c builtins/builtin_utils.c                         \
	builtins/environment_utils.c                                      \
	builtins/environment_utils_2.c                                    \
	builtins/environment_utils_3.c

OBJECTS_MINISHELL = $(SRC_MINISHELL:.c=.o)

OBJECTS_DEBUG = $(addprefix debug/, $(SRC_MINISHELL:.c=.o))

DEBUG_MINISHELL = debug/minishell

all: $(NAME0)

$(LIBFT):
	make -C libft

$(NAME0): $(LIBFT) $(OBJECTS_MINISHELL)
	$(CC) $(FLAGS) $(OBJECTS_MINISHELL) $(LIBFT) -lreadline $(HEADER) -o $(NAME0)

%.o: %.c
	 $(CC) $(FLAGS) -c $< -o $@

debug/%.o: %.c
	 $(CC) $(FLAGS) -c -g $< -o $@

clean:
	rm -f */*.o

fclean: clean
	rm -f $(NAME0)
	rm -f $(LIBFT)
	rm -rf debug/

re: fclean all

create_debug_dir:
	mkdir -p debug/builtins

debug: $(LIBFT) create_debug_dir $(OBJECTS_DEBUG)
	$(CC) -g $(FLAGS) $(OBJECTS_DEBUG) $(LIBFT) -lreadline $(HEADER) -o debug/$(NAME0)

valgrind: debug
	rm -f valgrind_output.txt
	valgrind --log-fd=1 --track-origins=yes --leak-check=full --show-leak-kinds=all $(DEBUG_MINISHELL) | tee valgrind_output.txt

gdb: debug
	gdb $(DEBUG_MINISHELL)

.PHONY: all clean fclean re valgrind gdb
