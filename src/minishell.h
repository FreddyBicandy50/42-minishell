/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/13 13:40:35 by amokdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_cmd
{
    char *command;
    char *flag;
    char *arg;
    struct s_cmd *next;
} t_cmd;

typedef struct s_data
{
    char *input;
} t_data;

#define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

// signals
void handle_sigint(int sig);
void handle_eof(void);
void handle_sigquit(__attribute__((unused)) int sig);
void handle_sigint(int sig);
void signals(void);
void handle_eof(void);

// libft
t_cmd *ft_cmd_lst_new(char *command);
void ft_cmd_add_back(t_cmd **lst, t_cmd *new);
int ft_strlen(const char *str);
char *ft_strncpy(size_t start, size_t end, char *src);

// utils
char *skip_spaces(char *str);
int printable(char c);

// lexering
void lexering(t_data *data);

//check_cmd
void	check_cmd_if_in(struct s_cmd);

#endif