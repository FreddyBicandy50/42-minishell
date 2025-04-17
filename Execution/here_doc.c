/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:34:42 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/17 13:16:48 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = 130;
	exit(0);
}

void	signal_heredoc(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

char	**inside_while(t_env **env, char *eof, char **input_line, int fd)
{
	while (1)
	{
		signal_heredoc();
		(*env)->here_doc = TRUE;
		if (!eof || g_signal == 130)
			break ;
		input_line[0] = readline(">");
		if (input_line[0] == NULL || g_signal == 130)
		{
			free(input_line[0]);
			break ;
		}
		if ((*env)->quote_indentifier == FALSE)
			input_line = expansion(*env, input_line);
		if (is_delimiter(input_line[0], eof))
		{
			free(input_line[0]);
			break ;
		}
		write(fd, input_line[0], ft_strlen(input_line[0]));
		write(fd, "\n", 1);
		free(input_line[0]);
	}
	return (input_line);
}

void	handle_heredoc(t_env **env, char *eof)
{
	char	**input_line;
	int		fd;
	int		pid;


	fd = 0;
	pid = fork();
	if (pid == -1)
		ft_error(env, "error fork in heredoc", 0, 0);
	if (pid == 0)
	{
		if (!eof)
			exit(STDIN_FILENO);
		fd = open("/tmp/heredoc_input", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			ft_error(env, "Error opening temporary file for heredoc", 1, false);
		input_line = malloc(sizeof(char *) * 2);
		input_line[1] = NULL;
		input_line = inside_while(env, eof, input_line, fd);
		(*env)->here_doc = FALSE;
		free(input_line);
		exit(0);
	}
	else
		wait(NULL);
}
