NAME = minishell
INCLUDES = ./src/
LIBFT = ./libraries/libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror  -I$(INCLUDES)

SRCS = main.c \
	   src/lexer.c

OBJECTS = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJECTS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJECTS)  $(LIBFT) -lreadline -o $(NAME) 

$(LIBFT):
	@make -C ./libraries/Libft

clean:
	@make clean -C ./libraries/libft
	rm -f $(OBJECTS)
	@clear

fclean: clean
	@make fclean -C ./libraries/libft
	rm -f $(NAME)
	@clear

re: fclean all

.PHONY: all clean fclean re
