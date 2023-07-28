# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 15:26:25 by vharkush          #+#    #+#              #
#    Updated: 2023/07/26 21:51:12 by vharkush         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ./libft/libft.a

NAME = ./minishell

SRCS =	src/main.c	\
		src/env.c	\
		src/builtin_env.c \
		src/builtin_pwd.c

CC = cc

CFLAGS = -g -Wextra -Werror -Wall

CPPFLAGS = -I ./incl

OBJS = $(SRCS:.c=.o)

all:    $(NAME)

$(NAME): $(OBJS)
		$(MAKE) -C ./libft
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT)

clean:
		$(MAKE) clean -C ./libft
		rm -rf $(OBJS)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re