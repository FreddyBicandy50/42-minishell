# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 12:28:36 by fbicandy          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/10/13 13:52:14 by amokdad          ###   ########.fr        #
=======
#    Updated: 2024/10/12 22:14:50 by fbicandy         ###   ########.fr        #
>>>>>>> refs/remotes/origin/main
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SOURCES = \
ft_cmd_lst.c \
ft_strlen.c \
<<<<<<< HEAD
ft_strncpy.c \
ft_strcmp.c
=======
ft_strcat.c \
ft_strncmp.c \
ft_strsub.c \
ft_strncpy.c 
>>>>>>> refs/remotes/origin/main

OBJECTS = $(SOURCES:.c=.o)

CC = gcc
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