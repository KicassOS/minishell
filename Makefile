# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 17:58:27 by iazimzha          #+#    #+#              #
#    Updated: 2023/02/05 18:46:55 by pszleper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME0 = minishell

HEADER = inc/minishell.h

LIBFT = libft/libft.a

SRC_MINISHELL = $(addprefix src/, builtin_utils.c cd_utils.c env.c environment_utils.c \
	executor_1.c executor_3.c exit.c expander_1.c expander_3.c \
	export.c free_0.c free_1.c main_utils.c parser_1.c parser_3.c \
	quote.c tokenizer_0.c tokenizer_2.c utils_0.c utils_2.c cd.c \
	echo.c environment_utils_2.c executor_0.c executor_2.c \
	executor_4.c expander_0.c expander_2.c export_2.c \
	main.c parser_0.c parser_2.c pwd.c signal.c \
	tokenizer_1.c unset.c utils_1.c)

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
	mkdir -p debug/src

debug: $(LIBFT) create_debug_dir $(OBJECTS_DEBUG)
	$(CC) -g $(FLAGS) $(OBJECTS_DEBUG) $(LIBFT) -lreadline $(HEADER) -o debug/$(NAME0)

valgrind: debug
	rm -f valgrind_output.txt
	valgrind --log-fd=1 --track-origins=yes --leak-check=full --show-leak-kinds=all $(DEBUG_MINISHELL) | tee valgrind_output.txt

gdb: debug
	gdb $(DEBUG_MINISHELL)

.PHONY: all clean fclean re valgrind gdb
