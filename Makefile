

LIBFT = ./libft/libft.a

LIB= -lreadline -lcurses

NAME = ./minishell

SRCS =	src/main.c						\
		src/env.c						\
		src/exec.c						\
		src/exec_utils.c				\
		src/redirects.c					\
		src/utils.c						\
		src/free.c						\
		src/quote.c						\
		src/input_check.c				\
		src/tokenizing.c				\
		src/input_utils.c				\
		src/signal.c					\
		src/ft_expander.c				\
		src/token.c						\
		src/ft_command_split.c			\
		src/shlvl.c						\
		src/error.c						\
		builtins/cd.c					\
		builtins/env.c	 				\
		builtins/pwd.c					\
		builtins/export.c				\
		builtins/unset.c				\
		builtins/builtins.c				\
		builtins/echo.c					\
		builtins/exit.c					\
		get_next_line/get_next_line.c	\
		get_next_line/get_next_line_utils.c


CC = cc

CFLAGS = -g -gdwarf-4 -Wextra -Werror -Wall

CPPFLAGS = -I ./incl

OBJS = $(SRCS:.c=.o)

all:    $(NAME)

$(NAME): $(OBJS)
		$(MAKE) -C ./libft
		$(CC) -o $(NAME) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT) $(LIB)

clean:
		$(MAKE) clean -C ./libft
		rm -rf $(OBJS)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
