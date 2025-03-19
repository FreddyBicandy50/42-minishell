/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:24:52 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/03/19 14:36:04 by marvin           ###   ########.fr       */
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

void	handle_heredoc(t_redir *redir)
{
	char	input_buffer[1024];
	FILE	*input_stream;
	int		fd;

	input_stream = fopen("/tmp/heredoc_input.txt", "w+");
	if (input_stream == NULL)
	{
		perror("Error opening temporary file for heredoc");
		exit(1);
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		fgets(input_buffer, sizeof(input_buffer), stdin);
		if (strncmp(input_buffer, redir->filename,
				strlen(redir->filename)) == 0)
			break ;
		fputs(input_buffer, input_stream);
	}
	fclose(input_stream);
	fd = open("/tmp/heredoc_input.txt", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_append(t_redir *redir)
{
	int		fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Append redirection failed");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_write(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Output redirection failed");
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output to file");
		exit(1);
	}
	close(fd);
}

void	handle_redirection(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;

	if (cmd->redirections)
		redir = cmd->redirections;
	else 
		return ;
	printf("Redirecting to file: %s\n", redir->filename);
	printf("Redirecting type: %d\n", redir->type);
	while (redir != NULL)
	{
		if (redir->type == 1)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd == -1)
			{
				perror("Input redirection failed");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == 2)
			handle_write(redir);
		else if (redir->type == 4)
			handle_append(redir);
		// else if (ft_strcmp(redir->type, "<<") == 0)
		// 	handle_heredoc(redir);
		redir = redir->next;
	}
}

void	restore_std(t_cmd *cmd)
{
	t_redir	*redir;
	int		saved_stdin;
	int		saved_stdout;


	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1) {
		perror("Error saving STDIN");
		exit(1);
	}
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1) {
		perror("Error saving STDOUT");
		exit(1);
	}
	redir = cmd->redirections;
	while (redir != NULL)
	{
		if (redir->type == 1)
		{
			dup2(saved_stdin, STDIN_FILENO);
		}
		else if (redir->type == 2 || redir->type == 4)
		{
			dup2(saved_stdout, STDOUT_FILENO);
		}
		redir = redir->next;
	}
	close(saved_stdin);
	close(saved_stdout);
}