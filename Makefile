NAME = minishell
INCLUDES = ./src/
LIBFT = ./Libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g  -I$(INCLUDES)
SRCS = main.c \
	Builtin/cd.c Builtin/echo.c Builtin/env.c Builtin/exit.c Builtin/export.c Builtin/pwd.c Builtin/unset.c \
	Execution/executing.c Execution/helper_execute.c Execution/redirections.c \
	Get_next_line/get_next_line.c Get_next_line/get_next_line_utils.c \
	System/set_env.c  System/signals.c \
	Tokenization/parsing.c Tokenization/helper_parser.c  Tokenization/helper_functions.c \

OBJECTS = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJECTS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJECTS)  $(LIBFT) -lreadline -o $(NAME) 

$(LIBFT):
	@make -C ./Libft

clean:
	@make clean -C ./Libft
	rm -f $(OBJECTS)
	clear
fclean: clean
	@make fclean -C ./Libft
	rm -f $(NAME)
	clear
re: fclean all

.PHONY: all clean fclean re
