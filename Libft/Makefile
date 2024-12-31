#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 12:28:36 by fbicandy          #+#    #+#              #
#    Updated: 2024/12/31 13:17:16 by amokdad          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a
SOURCES = \
ft_cmd_lst.c\
ft_error.c\
ft_lastword.c\
ft_lst.c\
ft_quote_handler.c\
ft_quote_identifier.c\
ft_split.c\
ft_strcat.c\
ft_strcmp.c\
ft_strdup.c\
ft_strjoin.c\
ft_strlen.c\
ft_strncpy.c\
ft_strnstr.c\
ft_strsub.c\
ft_word_count.c\
ft_strlcpy.c\
ft_stralicat.c

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