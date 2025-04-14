/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:24:52 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/14 23:13:50 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// handel redirection
// for redire->type :
// 1(< ) ----> reade from file.
// 2(> ) ----> Clears the file content before writing.
// 4(>>) ---->  Adds new data to the end of the file
// 			without removing existing content.
// 3(<<) ----> open heredoc

// int	handle_heredoc(t_env **env, t_redir *redir)
// {
// 	char	input_buffer[1024];
// 	FILE	*input_stream;
// 	int		fd;

// 	(void)redir;
// 	input_stream = fopen("/tmp/heredoc_input.txt", "w+");
// 	if (input_stream == NULL)
// 	{
// 		perror("Error opening temporary file for heredoc");
// 		exit(1);
// 	}
// 	while (1)
// 	{
// 		write(1, "heredoc>", 9);
// 		read(STDIN_FILENO, input_buffer, sizeof(input_buffer));
// 		if (strncmp(input_buffer, redir->filename,
// 				strlen(redir->filename)) == 0)
// 			break ;
// 		fputs(input_buffer, input_stream);
// 	}
// 	fclose(input_stream);
// 	fd = open("/tmp/heredoc_input.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_error(env, "heredoc redirection failed", 1, false);
// 		return (STDIN_FILENO);
// 	}
// 	return (fd);
// }

static bool	is_delimiter(const char *buffer, const char *delimiter)
{
	size_t	len;

	len = (size_t)ft_strlen((char *)delimiter);
	return (ft_strncmp(buffer, delimiter, len) == 0 && (buffer[len] == '\n'
			|| buffer[len] == '\0'));
}

int	handle_heredoc(t_env **env, char *eof)
{
	char	**input_line;
	int		fd;

	if (!eof || g_signal == 130)
		return (STDIN_FILENO);
	fd = open("/tmp/heredoc_input", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		ft_error(env, "Error opening temporary file for heredoc", 1, false);
	input_line = malloc(sizeof(char *) * 2);
	input_line[1] = NULL;
	while (1)
	{
		write(1, ">", 1);
		input_line[0] = (char *)malloc(BUFFER_SIZE * sizeof(char));
		if (read(STDIN_FILENO, input_line[0], BUFFER_SIZE - 1) <= 0)
		{
			free(input_line[0]);
			break ;
		}
		if (input_line[0])
			input_line[0][ft_strcspn(input_line[0], "\n")] = '\0';
		input_line = expansion(*env, input_line);
		if (is_delimiter(input_line[0], eof) || g_signal == 130)
		{
			free(input_line[0]);
			break ;
		}
		write(fd, input_line[0], ft_strlen(input_line[0]));
		write(fd, "\n", 1);
		free(input_line[0]);
	}
	free(input_line);
	fd = open("/tmp/heredoc_input.txt", O_RDONLY);
	if (fd == -1)
		ft_error(env, "heredoc redirection failed", 1, false);
	return (fd);
}

int	handle_append(t_env **env, t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_error(env, "Append redirection failed", 1, false);
		return (STDOUT_FILENO);
	}
	return (fd);
}

int	handle_write(t_env **env, t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_error(env, "Output redirection failed", 1, false);
		return (STDOUT_FILENO);
	}
	return (fd);
}

int	handle_read_file(t_env **env, t_redir *redir, bool here_doc)
{
	int	fd;

	if (here_doc)
		fd = open("/tmp/heredoc_input", O_RDONLY);
	else
		fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_error(env, "Input redirection failed", 0, false);
		return (STDIN_FILENO);
	}
	return (fd);
}

t_fd	handle_redirection(t_env **env, t_cmd *cmd)
{
	t_redir	*redir;
	t_fd	f;

	f.fd_1 = STDIN_FILENO;
	f.fd_2 = STDOUT_FILENO;
	redir = cmd->redirections;
	if (redir == NULL)
		return (f);
	while (redir)
	{
		if (redir->type == 1)
			f.fd_1 = handle_read_file(env, redir, FALSE);
		else if (redir->type == 2)
			f.fd_2 = handle_write(env, redir);
		else if (redir->type == 3)
			f.fd_1 = handle_read_file(env, redir, TRUE);
		else if (redir->type == 4)
			f.fd_2 = handle_append(env, redir);
		redir = redir->next;
	}
	return (f);
}

// void	restore_std(t_cmd *cmd, t_fd f)
// {
// 	t_redir	*redir;

// 	redir = cmd->redirections;
// 	if (redir == NULL)
// 		return ;
// 	dup(f.fd_2);
// 	dup(f.fd_1);
// 	if (f.fd_1 != STDIN_FILENO)
// 		if (dup2(f.fd_1, STDIN_FILENO) == -1)
// 			perror("Error restoring stdin");
// 	if (f.fd_2 != STDOUT_FILENO)
// 		if (dup2(f.fd_2, STDOUT_FILENO) == -1)
// 			perror("Error restoring stdout");
// 	if (f.fd_1 != STDIN_FILENO)
// 		close(f.fd_1);
// 	if (f.fd_2 != STDOUT_FILENO)
// 		close(f.fd_2);
// }
