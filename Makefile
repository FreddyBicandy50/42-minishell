NAME = minishell
INCLUDES = ./src/
LIBFT = ./Libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g  -I$(INCLUDES)
SRCS = main.c \
	Builtin/cd.c Builtin/echo.c Builtin/env.c Builtin/exit.c Builtin/export.c Builtin/helper_export.c Builtin/pwd.c Builtin/unset.c \
	Execution/executing.c Execution/helper_execute.c Execution/helper_execute2.c Execution/helper_execute3.c Execution/helper_execute4.c \
	Execution/helper_execute5.c Execution/helper_redirections.c Execution/redirections.c \
	Get_next_line/get_next_line.c Get_next_line/get_next_line_utils.c \
	System/set_env.c  System/signals.c\
	Tokenization/tokenizing.c Tokenization/helper_tokenizer.c  Tokenization/helper_functions.c Tokenization/helper_expander.c  \

OBJECTS = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJECTS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJECTS)  $(LIBFT) -lreadline -o $(NAME) 

$(LIBFT):
	@make -C ./Libft

clean:
	@make clean -C ./Libft
	rm -f $(OBJECTS)
fclean: clean
	@make fclean -C ./Libft
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
