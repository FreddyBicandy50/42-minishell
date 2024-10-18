NAME = minishell
INCLUDES = ./src/
LIBFT = ./Libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror  -I$(INCLUDES)

SRCS = main.c \
	tools/lexer_utils.c tools/helper_functions.c  \
	src/lexering.c  src/parsering.c  src/signals.c src/check_cmd.c

OBJECTS = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJECTS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJECTS)  $(LIBFT) -lreadline -o $(NAME) 

$(LIBFT):
	@make -C ./Libft

clean:
	@make clean -C ./Libft
	rm -f $(OBJECTS)
	@clear

fclean: clean
	@make fclean -C ./Libft
	rm -f $(NAME)
	@clear

re: fclean all

.PHONY: all clean fclean re
