# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 12:28:36 by fbicandy          #+#    #+#              #
#    Updated: 2024/11/01 19:45:23 by fredybicand      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SOURCES = \
ft_cmd_lst.c \
ft_strlen.c \
ft_strndup.c \
ft_strcat.c \
ft_strncmp.c \
ft_strcmp.c \
ft_strsub.c \
ft_strdup.c \
ft_split.c \
ft_strjoin.c \
ft_strncpy.c \
ft_strnstr.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) -r $@ $?

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re