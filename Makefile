NAME = minishell

LIBFT_NAME = libft.a
READLINE_NAME = readline.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3
CFLAGS += -I $(INC_DIR) -I $(LIBFT_DIR) -I /Users/$(USER)/.brew/opt/readline/include
CFLAGS += "-I/Users/$(USER)/.brew/opt/readline/include"

LDFLAGS = -L $(LIBFT_DIR)
LDFLAGS += "-L/Users/$(USER)/.brew/opt/readline/lib"

LDLIBS = -lft
LDLIBS += -lreadline

OBJ_DIR = objects
SRC_DIR = sources
INC_DIR = includes
LIBFT_DIR = libft

SRCS_EXEC_DIR = exec
SRCS_PARSE_DIR = parse

SRCS_EXEC = main_exec.c \
			list_to_struct.c \
			exec.c \
			redir.c \
			heredoc.c \
			env.c \
			utils.c \
			builtin.c 

SRCS_PARSE = init_exec.c

SRCS = main.c

SRCS_NAME = $(addprefix $(SRCS_EXEC_DIR)/, $(SRCS_EXEC)) \
			$(addprefix $(SRCS_PARSE_DIR)/, $(SRCS_PARSE)) \
			$(SRCS)

OBJS_NAME_DIR = $(SRCS_EXEC_DIR) $(SRCS_PARSE_DIR)
OBJS_DIR = $(addprefix $(OBJ_DIR)/,$(OBJS_NAME_DIR))
OBJS_NAME = $(SRCS_NAME:%.c=%.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJS_NAME))


.PHONY: all re clean fclean

all: $(NAME)


$(NAME): $(OBJS) 
	make -C $(LIBFT_DIR)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

debug: CFLAGS += -g3 -fsanitize=address 
debug: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): | $(OBJ_DIR) $(OBJS_DIR)

$(OBJ_DIR): 
	mkdir -p $(OBJ_DIR) 2> /dev/null

$(OBJS_DIR): 
	mkdir -p $(OBJS_DIR) 2> /dev/null

clean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
