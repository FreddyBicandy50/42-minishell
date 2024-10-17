/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/17 20:41:32 by fbicandy         ###   ########.fr       */
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
	char			**arg;
	char			*flag;
	int				arg_number;
	int				pipe;
	int				redir_in;
	int				redir_out;
	int				redir_append;
	int				redir_heredoc;
	struct s_cmd	*next;
}	t_cmd;

// signals
void	signals(void);
void	handle_eof(void);
void	handle_eof(void);
void	handle_sigint(int sig);
void	handle_sigint(int sig);
void	handle_sigquit(__attribute__((unused)) int sig);

// libft
t_cmd	*ft_cmd_lst_new(char *command);

int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	free_cmd(t_cmd *cmd);
void	print_cmd_list(t_cmd *cmd);
void	ft_cmd_add_back(t_cmd **lst, t_cmd *new);
void	add_first_cmd(t_cmd **cmd, char *command);

char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat(const char *dest, const char *src);
char	*ft_strncpy(size_t start, size_t end, char *src);
char	*ft_strsub(const char *s, unsigned int start, size_t len);

// lexering
int		get_next_str(t_cmd **cmd, char *prompt);
void	lexering( char *input);

// lexer utils
int		check_quote(char c, int quote);
int		update_flags(t_cmd **cmd, int i, char *prompt, char *all_flags);

void	append_cmd(t_cmd **cmd, char *command);
void	handle_pipe_redirection(t_cmd **cmd, char *prompt);

char	*get_args(t_cmd **cmd, int i, char *prompt);

	// utils
int		pipe_redirections(char *str, int *is_double);
int		printable(char c);
char	*skip_spaces(char *str);

// check_cmd
void	check_cmd_if_included(t_cmd *cmd);

#endif