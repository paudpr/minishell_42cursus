NAME = minishell

LIBFT_NAME = libft.a
READLINE_NAME = readline.a

MAKE = make

CC = gcc

CFLAGS = -Wall -Werror -Wextra
CFLAGS += -D BUFFER_SIZE=10;
CFLAGS += -03
CFLAGS += -L/usr/local/opt/readline/lib