/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/26 18:53:49 by fbicandy         ###   ########.fr       */
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

extern char	**environ;

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*command;
	char			**arg;
	char			*flag;
	int				arg_number;
	int				pipe;
	char			*filename;
	t_redir			*redirections;
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
char	**ft_command_split(char *s, char c);
int		isquote(char c);
char	*get_next_command(t_cmd **cmd, char *prompt);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_split(char **args);
void	free_cmd(t_cmd *cmd);
void	print_cmd_list(t_cmd *cmd);
void	ft_cmd_add_back(t_cmd **lst, t_cmd *new);
void	add_first_cmd(t_cmd **cmd, char *command);
void	ft_error(t_cmd **cmd, char *message, char *str);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat(const char *dest, const char *src);
char	*ft_strdup_until_space(const char *str);
char	*ft_strncpy(size_t start, size_t end, char *src);
char	*ft_strsub(const char *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_last_word(t_cmd **cmd, int type, char *prompt);
char	*get_next_word(char *prompt);

// get_next_line
char	*get_next_line(int fd);

// parse
void	parser(t_cmd **cmd, char *envp[]);

// lexering
int		get_next_str(t_cmd **cmd, char *prompt);

	// lexer utils
int		type_redirection(char redirection, int redirection_count);
int		check_quote(char c, int quote);
int		update_flags(t_cmd **cmd, int i, char *prompt, char *all_flags);

void	append_redirection(t_cmd **cmd, int type, char *filename);
void	append_cmd(t_cmd **cmd, char *command);
int		handle_pipe_redirection(t_cmd **cmd, char *prompt);

char	*get_args(t_cmd **cmd, int i, char *prompt);

	// utils
int		pipe_redirections(char *str, int *is_double);
int		printable(char c);
char	*skip_spaces(char *str);

// helper_parser
int		built_in_functions(t_cmd **cmd, char **envp);
char	*find_path(char *cmd, char **envp);
void	excute_with_flags(char *path, t_cmd **cmd, char*envp[]);

// echo
void	echo_cmd(t_cmd **cmd);

//PWD
void	pwd_cmd(void);

//ENV
void	env_cmd(void);

//CD
void	cd_cmd(t_cmd **cmd);

//EXIT
void	exit_minishell(void);

//UNSET
void	my_unset(t_cmd **cmd);

#endif