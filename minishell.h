/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/07 19:06:51 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

extern int			g_signal;
# define PROMPT "\001\e[33m\00242-minishell\001\e[32m\002 ➜\001\e[0m\002 "

typedef struct s_fd
{
	int				fd_1;
	int				fd_2;
}					t_fd;

typedef struct s_expand
{
	char			*section;
	char			*prev_section;
	char			*next_section;
	char			*var_value;
	int				len_section;
	char			**expanded_segements;
}					t_expand;

typedef struct s_env
{
	char			*variable_name;
	char			*value;
	int				exit_code;
	bool			exit_status;
	bool			expanding;
	struct s_env	*next;
}					t_env;

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*command;
	char			**arg;
	char			*flag;
	int				arg_number;
	t_redir			*redirections;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipe
{
	int	fd[2];
	int	saved_fd;
}	t_pipe;

// Built Folder
// cd.c
void				cd_cmd(t_cmd **cmd, t_env **env);
// echo.c
void				echo_cmd(t_cmd **cmd);
// env.c
void				env_cmd(t_env **env);
// exit.c
void				exit_minishell(void);
// export.c
void				my_export(t_cmd **cmd, t_env **env);
// pwd.c
void				pwd_cmd(void);
// unset.c
void				my_unset(t_cmd **cmd, char **envp);

// Execution Folder
// exectuting.c
void				check_cmd(t_cmd **cmd, char *envp[], t_env **env);
void				executing(t_cmd **cmd, char *envp[], t_env **env);
void				execute(char *path, t_cmd **cmd, char *envp[]);
t_fd				handle_redirection(t_cmd *cmd);
// helper_execute.c
char				*find_path(char *cmd, char **envp);
int					built_in_functions(t_cmd **cmd, char **envp, t_env **env);

//helper_execute2.c
void				handle_parent_process(t_pipe *pipe_fd, t_cmd **cmd);
void				handle_child_process(t_cmd **cmd, t_pipe pipe_fd,
						t_env **env, char *envp[]);
pid_t				create_process(void);
int					create_pipe(int fd[2]);
void				wait_for_children(void);

//helper_redirections.c
void				restore_original_fds(int original_stdin,
						int original_stdout);
int					save_original_fds(int *original_stdin,
						int *original_stdout);

// Get_next_line Folder
// get_next_line.c
char				*get_next_line(int fd);

// Libft Folder
// ft_char_is.c
int					isquote(char c);
int					redirections(char c1, char c2);
int					isprintable(char c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
// ft_strcat.c
void				ft_strcat(char *dest, const char *src);
// ft_strchr.c
char				*ft_strchr(char const *str, int c);
// ft_strcmp.c
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
// ft_strdup.c
char				*ft_strdup(char *s);
char				*ft_strndup(const char *s, size_t n);
// ft_strjoin.c
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strjoin_extra(char *s1, char *s2, int len_extra);
char				*ft_strjoin_free(char *s1, char *s2);
// ft_strlcpy.c
size_t				ft_strlcpy(char *dst, char *src, size_t size);
// ft_strlen.c
int					ft_strlen(char *str);
// ft_strnstr.c
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
// ft_split.c
char				**ft_split(char *s, char c);
char				**ft_shell_split(char *s, char c);
void				free_split(char **args);
// ft_strtrim.c
char				*skip_spaces(char *str);
// ft_struct_list.c
void				struct_addback_list(t_cmd **cmd, t_cmd *new_cmd);
t_cmd				*struct_get_first(t_cmd *cmd);
t_cmd				*struct_create_list(char *command, t_cmd *current);
void				struct_add_first_cmd(t_cmd **cmd, char *argument);
void				struct_free_redirections(t_redir *redirections);
void				struct_free_cmd(t_cmd *cmd);
// ft_struct_update_lst.c
void				struct_update_flags(t_cmd **cmd, char *flag,
						char *all_flags);
void				struct_update_args(t_cmd **cmd, char *command);
void				struct_update_redirection(t_cmd **cmd, int type,
						char *filename);
void				struct_print_list(t_cmd *cmd);
// ft_word_count.c
size_t				ft_wordcount(char *s, char c);

// System Folder
// set_env.c
void				free_envp(t_env *env);
t_env				*save_envp(char **envp);
void				set_env(char *var, char *value, t_env **env);
char				*get_env_value(t_env *env, char *key);
// signals.c
void				ft_error(t_env **env, char *errmessage, int error_code);
void				signals(void);
void				handle_eof(void);
void				handle_eof(void);
void				handle_sigint(int sig);
void				handle_sigint(int sig);
void				handle_sigquit(__attribute__((unused)) int sig);

// Tokenization Folder
// tokenizing.c
t_cmd				*tokenizing(char *prompt, t_env *env);
char				*rediretions_token(t_cmd **cmd, char *prompt, t_env *env);
char				*args_token(t_cmd **cmd, int i, char *prompt, t_env *env);
char				*flags_token(t_cmd **cmd, char *prompt, t_env *env);
char				*command_token(t_cmd **cmd, char *prompt, t_env *env,
						int type);
// helper_expander.c
int					init_expansion(t_expand *expander, char **segments);
void				expansion_mechanism(t_expand *expander, t_env *env);
int					expander_quotes(char *s, int start, int end, char **dest);
int					expansion_quotes(int index, char *s, char **dest,
						t_env *env);

// helper_functions.c
int					redirection_param(t_cmd **cmd, char *prompt, int type,
						t_env *env);
char				*skip_to_c(char *s, char c, bool expanding);
int					copy_flag(t_cmd **cmd, int i, char *prompt, t_env *env);
// helper_tokenizer.c
char				*skip_inside(char quote, char *s);
char				*dequotencpy(int start, int end, char *s);
int					copy_args(t_cmd **cmd, char *prompt, t_env *env);
int					redirections(char c1, char c2);
char				**expansion(t_env *env, char **segments);

#endif