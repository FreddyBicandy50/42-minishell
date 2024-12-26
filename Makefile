NAME = minishell
INCLUDES = ./src/
LIBFT = ./Libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g  -I$(INCLUDES)
SRCS = main.c \
	tools/helper_parser.c tools/helper_lexer.c tools/helper_functions.c  \
	src/lexering.c  src/parsering.c  src/signals.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	built_in/echo.c built_in/pwd.c built_in/env.c built_in/cd.c built_in/exit.c

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
