/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:04 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/31 22:47:37 by fbicandy         ###   ########.fr       */
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
	struct s_cmd	*next;
}	t_cmd;

// SIGNALS
void	signals(void);
void	handle_eof(void);
void	handle_eof(void);
void	handle_sigint(int sig);
void	handle_sigint(int sig);
void	handle_sigquit(__attribute__((unused)) int sig);

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
	//GET NEXT LINE
char	*get_next_line(int fd);

// Libft
	//FT CMD_LST
t_cmd	*struct_create_list(char *command);
void	struct_addback_list(t_cmd **lst, t_cmd *new);
void	struct_update_flags(t_cmd **cmd, char *flag, char *all_flags);
void	struct_update_args(t_cmd **cmd, char *command);
void	struct_free_redirections(t_redir *redirections);
void	struct_free_cmd(t_cmd *cmd);
void	print_cmd_list(t_cmd *cmd);
	//FT WORDCOUNT
size_t	ft_wordcount(char *s, char c);
	//FT SPLIT
char	**ft_split(char *s, char c);
char	**ft_shell_split(char *s, char c);
void	free_split(char **args);
	//FT QUOTE HANDLER
char	*skip_to_c(char *s, char c);
char	*skip_inside(char quote, char *s);
	//FT QUOTE IDENTIFIER
char	*dequotencpy(int start,int end, char *s);
int		isquote(char c);
char	*isprintable_quote(char *s);
	//FT STRLCAT
size_t	ft_strlcat(char *dst, const char *src, size_t size);
	//FT STRLEN
int		ft_strlen(const char *str);
	//FT STRCMP
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
	//FT ERROR.c
void	ft_error(t_cmd **cmd, char *message, char *str);
	//FT STRDUP.c
char	*ft_strdup(char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strdup_until_space(char *str);
	//FT STRJOIN
char	*ft_strjoin(char *s1, char *s2);
	//FT STRLCPY
size_t	ft_strlcpy(char *dst, char *src, size_t size);
// FT STRCAT
char	*ft_strcat(char *dest, const char *src);
	//FT STRNSTR
char	*ft_strnstr(const char *big, const char *little, size_t len);
	//FT LASTWORD
char	*ft_last_word(t_cmd **cmd, int type, char *prompt);
	//FT LST
void	ft_put_command(t_cmd **cmd, t_cmd *new_cmd);

//SRC
	//LEXERING
int		copy_args(t_cmd **cmd, char *prompt);
int		get_next_redirection(t_cmd **cmd, char *prompt);
char	*get_next_flag(t_cmd **cmd, char *prompt);
char	*flags_token(t_cmd **cmd, char *prompt);
void	tokenization(t_cmd **cmd, char *prompt);
	//PARESERING
void	parser(t_cmd **cmd, char *envp[]);

//TOOLS
	//HELPER_FUNCTIONS
int		copy_flag(t_cmd **cmd,int i, char *prompt);
char	*skip_spaces(char *str);
int		printable(char c);
int		pipe_redirections(char *str, int *is_double);
int		check_quote(char c, int quote);
	//HELPER_LEXER
char	*args_token(t_cmd **cmd, int i, char *prompt);
void	add_first_cmd(t_cmd **cmd, char *argument);
void	append_redirection(t_cmd **cmd, int type, char *filename);

	//HELPER_PARSER
char	*find_path(char *cmd, char **envp);
int		built_in_functions(t_cmd **cmd, char **envp);
	//set_env
void	set_env(char *var, char *value, char **envp);

#endif