# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 12:28:36 by fbicandy          #+#    #+#              #
#    Updated: 2025/02/01 15:05:50 by fbicandy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SOURCES = \
ft_char_is.c\
ft_strcat.c\
ft_strcmp.c\
ft_strdup.c\
ft_strjoin.c\
ft_strlcpy.c\
ft_strlen.c\
ft_strnstr.c\
ft_strsplit.c\
ft_strtrim.c\
ft_struct_lst.c\
ft_struct_update_lst.c\
ft_word_count.c

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