NAME = minishell

LIBFT_NAME = libft.a
READLINE_NAME = readline.a

MAKE = make

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3
#CFLAGS += -L/usr/local/opt/readline/lib
CFLAGS += -I $(INC_PATH) -I $(LIBFT_PATH) -I /Users/$(USER)/.brew/opt/readline/include
CFLAGS += "-I/Users/$(USER)/.brew/opt/readline/include"
#CFLAGS += -I/usr/local/include

LDFLAGS = -L $(LIBFT_PATH)
LDFLAGS += "-L/Users/$(USER)/.brew/opt/readline/lib"
#LDFLAGS += -L /usr/local/lib

LDLIBS = -lft
LDLIBS += -lreadline

OBJ_PATH = objects
SRC_PATH = sources
INC_PATH = includes
LIBFT_PATH = libft

SOURCES = readline.c

# SRCS_NAME = $(addprefix $(SRC_PATH)/, $(SOURCES))
# OBJS_PATH = $(addprefix $(OBJ_PATH)/, $(SOURCES))
OBJS_NAME = $(SOURCES:%.c=%.o)
OBJS = $(addprefix $(OBJ_PATH)/, $(OBJS_NAME))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $^ -o $@  $(CFLAGS) $(LDFLAGS) $(LDLIBS) 

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): | $(OBJ_PATH)

$(OBJ_PATH): 
	mkdir -p $(OBJ_PATH) 2> /dev/null

# $(OBJS_PATH): 
# 	mkdir -p $(OBJ_PATH)

debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

clean:
	make fclean -C $(LIBFT_PATH)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
