/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/12 16:07:37 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <curses.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stddef.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char			*command;
	char			*flag;
	char			*arg;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	*input;
}	t_data;

// signals
void	signals(void);
void	handle_eof(void);
void	handle_eof(void);
void	handle_sigint(int sig);
void	handle_sigint(int sig);
void	handle_sigquit(__attribute__((unused)) int sig);

// libft
int		ft_strlen(const char *str);
void	print_cmd_list(t_cmd *cmd);
t_cmd	*ft_cmd_lst_new(char *command);
void	ft_cmd_add_back(t_cmd **lst, t_cmd *new);
char	*ft_strcat(const char *dest, const char *src);
char	*ft_strncpy(size_t start, size_t end, char *src);

// utils
int		prd(char c);
int		printable(char c);
char	*skip_spaces(char *str);

// lexering
void	lexering(t_data *data);

#endif