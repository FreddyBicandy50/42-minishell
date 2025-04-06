/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:24:52 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/06 16:01:34 by aal-mokd         ###   ########.fr       */
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

// void	handle_heredoc(t_redir *redir)
// {
// 	char	input_buffer[1024];
// 	FILE	*input_stream;
// 	int		fd;

// 	input_stream = fopen("/tmp/heredoc_input.txt", "w+");
// 	if (input_stream == NULL)
// 	{
// 		perror("Error opening temporary file for heredoc");
// 		exit(1);
// 	}
// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		fgets(input_buffer, sizeof(input_buffer), stdin);
// 		if (strncmp(input_buffer, redir->filename,
// 				strlen(redir->filename)) == 0)
// 			break ;
// 		fputs(input_buffer, input_stream);
// 	}
// 	fclose(input_stream);
// 	fd = open("/tmp/heredoc_input.txt", O_RDONLY);
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// }

int	handle_append(t_redir *redir)
{
	int		fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Append redirection failed");
		return (STDOUT_FILENO);
	}
	return (fd);
}

int	handle_write(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Output redirection failed");
		return (STDOUT_FILENO);
	}
	return (fd);
}

int	handle_read_file(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Input redirection failed");
		return (STDIN_FILENO);
	}
	return (fd);
}

t_fd	handle_redirection(t_cmd *cmd)
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
			f.fd_1 = handle_read_file(redir);
		else if (redir->type == 2)
			f.fd_2 = handle_write(redir);
		else if (redir->type == 4)
			f.fd_2 = handle_append(redir);
		// else if (ft_strcmp(redir->type, "<<") == 0)
		// 	handle_heredoc(redir);
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
