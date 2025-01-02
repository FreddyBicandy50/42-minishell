/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:24:52 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/01/02 11:26:04 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void handle_heredoc(t_redir *redir)
{
	char input_buffer[1024];
	FILE *input_stream;
	int fd;

	input_stream = fopen("/tmp/heredoc_input.txt", "w+");
	if (input_stream == NULL)
	{
		perror("Error opening temporary file for heredoc");
		exit(1);
	}
	while (1)
	{
		printf("heredoc> ");
		fgets(input_buffer, sizeof(input_buffer), stdin);
		if (strncmp(input_buffer, redir->filename,
				strlen(redir->filename)) == 0)
		{
			break;
		}
		fputs(input_buffer, input_stream);
	}
	fclose(input_stream);

	fd = open("/tmp/heredoc_input.txt", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void handle_redirection(t_cmd *cmd)
{
	int fd;
	t_redir *redir = cmd->redirections;

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
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("Output redirection failed");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == 3)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("Append redirection failed");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == 4)
		{
			handle_heredoc(redir);
		}
		redir = redir->next;
	}
}