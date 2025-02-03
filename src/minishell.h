/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/03 19:51:16 by fbicandy         ###   ########.fr       */
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

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**var;
	char			*command;
	char			**arg;
	char			*flag;
	int				arg_number;
	int				pipe;
	char			*filename;
	t_redir			*redirections;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

//BUILT_INT
	// echo
void	echo_cmd(t_cmd **cmd);
	//PWD
void	pwd_cmd(void);
	//ENV
void	env_cmd(char **envp);
	//CD
void	cd_cmd(t_cmd **cmd, char **envp);
	//EXIT
void	exit_minishell(void);
	//EXPORT
void	my_export(t_cmd **cmd);
	//UNSET
void	my_unset(t_cmd **cmd, char **envp);

//GET_NEXT_LINE
	//GET NEXT LINE
char	*get_next_line(int fd);

// LIBFT
	//FT CHAR IS
int		isquote(char c);
int		redirections(char c1, char c2);
int		isprintable(char c);
	// FT STRCAT
char	*ft_strcat(char *dest, const char *src);
	//FT STRCMP
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
	//FT STRDUP.c
char	*ft_strdup(char *s);
char	*ft_strndup(const char *s, size_t n);
	//FT STRJOIN
char	*ft_strjoin(char *s1, char *s2);
	//FT STRLCPY
size_t	ft_strlcpy(char *dst, char *src, size_t size);
	//FT STRLEN
int		ft_strlen(char *str);
	//FT STRNSTR
char	*ft_strnstr(const char *big, const char *little, size_t len);
	//FT STRSPLIT
char	**ft_split(char *s, char c);
char	**ft_shell_split(char *s, char c);
void	free_split(char **args);
	//FT STRTRIM
char	*skip_spaces(char *str);
	// FT STRUCT_LST
t_cmd	*struct_addback_list(t_cmd **cmd, t_cmd *new_cmd);
t_cmd	*struct_get_first(t_cmd *cmd);
t_cmd	*struct_create_list(char *command, t_cmd *current);
void	struct_add_first_cmd(t_cmd **cmd, char *argument);
void	struct_free_redirections(t_redir *redirections);
void	struct_free_cmd(t_cmd *cmd);
	// FT FREE_STRUCT_LST
void	struct_update_flags(t_cmd **cmd, char *flag, char *all_flags);
void	struct_update_args(t_cmd **cmd, char *command);
void	struct_update_redirection(t_cmd **cmd, int type, char *filename);
void	struct_print_list(t_cmd *cmd);
// FT WORDCOUNT
size_t	ft_wordcount(char *s, char c);

//SRC
	//LEXERING
t_cmd	*tokenization(t_cmd *cmd, char *prompt);
char	*rediretions_token(t_cmd **cmd, char *prompt, int type);
char	*args_token(t_cmd **cmd, int i, char *prompt);
char	*flags_token(t_cmd **cmd, char *prompt);
char	*command_token(t_cmd **cmd, char *prompt);
int		copy_args(t_cmd **cmd, char *prompt);
	//PARESERING
void	execute(char *path, t_cmd **cmd, char *envp[]);
void	executing(t_cmd **cmd, char *envp[]);
void	check_cmd(t_cmd **cmd, char *envp[]);
	// SIGNALS
void	signals(void);
void	handle_eof(void);
void	handle_eof(void);
void	handle_sigint(int sig);
void	handle_sigint(int sig);
void	handle_sigquit(__attribute__((unused)) int sig);

//TOOLS
	//HELPER_FUNCTIONS
char	*redirection_near_redirirection(char *prompt);
void	ft_error(t_cmd **cmd, char *message, char *str);
char	*skip_to_c(char *s, char c);
int		copy_flag(t_cmd **cmd, int i, char *prompt);
	//HELPER_LEXER
char	*skip_inside(char quote, char *s);
char	*dequotencpy(int start, int end, char *s);
int		copy_args(t_cmd **cmd, char *prompt);
int		redirections(char c1, char c2);
	//HELPER_PARSER
char	*find_path(char *cmd, char **envp);
int		built_in_functions(t_cmd **cmd, char **envp);
	//PARESERING
void	executing(t_cmd **cmd, char *envp[]);
	//set_env
void	set_env(char *var, char *value, char **envp);

#endif