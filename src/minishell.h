/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/02 22:50:47 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_data
{
    char *input;
} t_data;

#define PROMPT "\e[45m>>>\e[0m\e[33m Minishell$\e[0m"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void    lexering(char *prompt);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_strlen(const char *str);
size_t  ft_strlcpy(char *dest, const char *src, size_t size);

#endif