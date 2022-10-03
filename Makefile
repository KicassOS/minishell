# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 20:34:13 by pszleper          #+#    #+#              #
#    Updated: 2022/10/03 03:53:45 by pszleper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror -c

NAME0 = minishell

HEADER = minishell.h

SRC_MINISHELL = main.c utils.c signal.c builtins/cd.c builtins/echo.c \
	builtins/env.c builtins/exit.c builtins/pwd.c builtins/export.c   \
	builtins/unset.c builtins/builtin_utils.c                         \
	builtins/environment_utils.c

OBJECTS_MINISHELL = $(SRC_MINISHELL:.c=.o)

all: libft.a $(NAME0)

libft.a:
	make -C Libft
	cp Libft/libft.a .
	cp Libft/libft.h .

$(NAME0): libft.a $(OBJECTS_MINISHELL)
	$(CC) $(OBJECTS_MINISHELL) libft.a -lreadline $(HEADER) -o $(NAME0)

%.o: %.c
	 $(CC) $(FLAGS) $< -o $@

clean:
	rm -f */*.o

fclean: clean
	rm -f $(NAME0)
	rm -f libft.a && rm -f libft.h

re: fclean all

.PHONY: all clean fclean re