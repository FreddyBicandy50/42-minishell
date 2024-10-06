/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/06 19:53:13 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_cmd
{
    char *cmd;
} s_data;

typedef struct s_data
{
    char *input;
} t_data;

#define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void lexering(t_data *data);
int ft_strlen(const char *str);
char *ft_strncpy(size_t start, size_t end, char *src);

#endif