/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2025/03/16 23:02:46 by fbicandy         ###   ########.fr       */
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


extern	int g_signal;
#define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"

typedef struct s_env
{
	char			*variable_name;
	bool			flag;
	int				exit_code;
	struct s_env	*next;
}	t_env;

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
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;


// Built Folder
	// cd.c
void	cd_cmd(t_cmd **cmd, char **envp);
	// echo.c
void	echo_cmd(t_cmd **cmd);
	// env.c
void	env_cmd(char **envp);
	// exit.c
void	exit_minishell(void);
	// export.c
void	my_export(t_cmd **cmd, char **envp);
	// pwd.c
void	pwd_cmd(void);
	// unset.c
void	my_unset(t_cmd **cmd, char **envp);


// Execution Folder
	// exectuting.c
void	executing(t_cmd **cmd, char *envp[]);
void	execute(char *path, t_cmd **cmd, char *envp[]);
void	executing(t_cmd **cmd, char *envp[]);
void	check_cmd(t_cmd **cmd, char *envp[]);
	// helper_execute.c
char	*find_path(char *cmd, char **envp);
int		built_in_functions(t_cmd **cmd, char **envp);

// Get_next_line Folder
	// get_next_line.c
char	*get_next_line(int fd);

// Libft Folder
	// ft_char_is.c
int		isquote(char c);
int		redirections(char c1, char c2);
int		isprintable(char c);
	// ft_strcat.c
void	ft_strcat(char *dest, const char *src);
	// ft_strchr.c
char	*ft_strchr(char const *str, int c);
	// ft_strcmp.c
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
	// ft_strdup.c
char	*ft_strdup(char *s);
char	*ft_strndup(const char *s, size_t n);
	// ft_strjoin.c
char	*ft_strjoin(char *s1, char *s2);
	// ft_strlcpy.c
size_t	ft_strlcpy(char *dst, char *src, size_t size);
	// ft_strlen.c
int		ft_strlen(char *str);
	// ft_strnstr.c
char	*ft_strnstr(const char *big, const char *little, size_t len);
	// ft_split.c
char	**ft_split(char *s, char c);
char	**ft_shell_split(char *s, char c);
void	free_split(char **args);
	// ft_strtrim.c
char	*skip_spaces(char *str);
	// ft_struct_list.c
void	struct_addback_list(t_cmd **cmd, t_cmd *new_cmd);
t_cmd	*struct_get_first(t_cmd *cmd);
t_cmd	*struct_create_list(char *command, t_cmd *current);
void	struct_add_first_cmd(t_cmd **cmd, char *argument);
void	struct_free_redirections(t_redir *redirections);
void	struct_free_cmd(t_cmd *cmd);
	// ft_struct_update_lst.c
void struct_update_flags(t_cmd **cmd, char *flag, char *all_flags);
void	struct_update_args(t_cmd **cmd, char *command);
void	struct_update_redirection(t_cmd **cmd, int type, char *filename);
void	struct_print_list(t_cmd *cmd);
	// ft_word_count.c
size_t	ft_wordcount(char *s, char c);

// System Folder
	// set_env.c
void	free_envp(t_env *env);
t_env	*save_envp(char **envp);
void	set_env(char *var, char *value, char **envp);
	// signals.c
void	signals();
void	handle_eof(void);
void	handle_eof(void);
void	handle_sigint(int sig);
void	handle_sigint(int sig);
void	handle_sigquit(__attribute__((unused)) int sig);

// Tokenization Folder
	// parsing.c
t_cmd	*parsing(char *prompt,t_env **env);
char	*rediretions_token(t_cmd **cmd, char *prompt);
char	*args_token(t_cmd **cmd, int i, char *prompt);
char	*flags_token(t_cmd **cmd, char *prompt);
char	*command_token(t_cmd **cmd, char *prompt);
int		copy_args(t_cmd **cmd, char *prompt);
	// helper_functions.c
int		redirection_param(t_cmd **cmd, char *prompt, int type);
void	ft_error(t_cmd **cmd, char *message, char *str);
char	*skip_to_c(char *s, char c);
int		copy_flag(t_cmd **cmd, int i, char *prompt);
	// helper_parser.c
char	*skip_inside(char quote, char *s);
char	*dequotencpy(int start, int end, char *s);
int		copy_args(t_cmd **cmd, char *prompt);
int		redirections(char c1, char c2);
void	expansion(t_cmd **cmd, char *str);


#endif