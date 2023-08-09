

LIBFT = ./libft/libft.a

LIB= -lreadline -lcurses

NAME = ./minishell

SRCS =	main.c	\
		env.c	\
		builtin_env.c \
		builtin_pwd.c	\
		pipex.c	\
		pipex_utils.c	\
		get_next_line/get_next_line.c	\
		get_next_line/get_next_line_utils.c


CC = cc

CFLAGS = -g -Wextra -Werror -Wall

CPPFLAGS = -I ./incl

OBJS = $(SRCS:.c=.o)

all:    $(NAME)

$(NAME): $(OBJS)
		$(MAKE) -C ./libft
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT) $(LIB)

clean:
		$(MAKE) clean -C ./libft
		rm -rf $(OBJS)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re