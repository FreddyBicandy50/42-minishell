NAME = minishell
INCLUDES = ./src/
LIBFT = ./Libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror  -I$(INCLUDES)

SRCS = main.c \
	src/utils.c \
	src/lexer.c  src/signals.c

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
