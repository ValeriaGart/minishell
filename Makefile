# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 15:26:25 by vharkush          #+#    #+#              #
#    Updated: 2023/07/25 15:26:49 by vharkush         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./minishell

SRCS =	src/main.c				\

CC = cc

CFLAGS = -g -Wextra -Werror -Wall

CPPFLAGS = -I ./incl

OBJS = $(SRCS:.c=.o)

all:    $(NAME)

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re