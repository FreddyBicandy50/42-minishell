/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/03 19:48:28 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *path, t_cmd **cmd, char *envp[])
{
	char	**exec_args;
	int		i;
	int		j;

	j = 0;
	i = 1;
	exec_args = malloc(sizeof(char *) * ((*cmd)->arg_number + 2));
	exec_args[0] = (*cmd)->command;
	while (j < (*cmd)->arg_number)
	{
		exec_args[i] = (*cmd)->arg[j];
		i++;
		j++;
	}
	if ((*cmd)->flag && *(*cmd)->flag)
	{
		exec_args[i] = (*cmd)->flag;
		exec_args[i + 1] = NULL;
	}
	else
		exec_args[i] = NULL;
	if (execve(path, exec_args, envp) == -1)
		printf("Error executing command");
	free(exec_args);
}

// void handle_heredoc(t_redir *redir)
// {
// 	char input_buffer[1024];
// 	FILE *input_stream;
// 	int fd;

// 	input_stream = fopen("/tmp/heredoc_input.txt", "w+");
// 	if (input_stream == NULL)
// 	{
// 		perror("Error opening temporary file for heredoc");
// 		exit(1);
// 	}
// 	while (1)
// 	{
// 		printf("heredoc> ");
// 		fgets(input_buffer, sizeof(input_buffer), stdin);
// 		if (strncmp(input_buffer, redir->filename,
// 				strlen(redir->filename)) == 0)
// 		{
// 			break;
// 		}
// 		fputs(input_buffer, input_stream);
// 	}
// 	fclose(input_stream);

// 	fd = open("/tmp/heredoc_input.txt", O_RDONLY);
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// }

// void handle_redirection(t_cmd *cmd)
// {
// 	int fd;
// 	t_redir *redir = cmd->redirections;

// 	while (redir != NULL)
// 	{
// 		if (redir->type == 1)
// 		{
// 			fd = open(redir->filename, O_RDONLY);
// 			if (fd == -1)
// 			{
// 				perror("Input redirection failed");
// 				exit(1);
// 			}
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		else if (redir->type == 2)
// 		{
// 			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd == -1)
// 			{
// 				perror("Output redirection failed");
// 				exit(1);
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (redir->type == 3)
// 		{
// 			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (fd == -1)
// 			{
// 				perror("Append redirection failed");
// 				exit(1);
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (redir->type == 4)
// 		{
// 			handle_heredoc(redir);
// 		}
// 		redir = redir->next;
// 	}
// }

void	check_cmd(t_cmd **cmd, char *envp[])
{
	char	*path;
	pid_t	pid;

	if (built_in_functions(cmd, envp) == 1)
	{
		path = find_path((*cmd)->command, envp);
		if (!path)
			return ;
		pid = fork();
		if (pid == 0)
		{
			// handle_redirection(*cmd);
			execute(path, cmd, envp);
		}
		else if (pid < 0)
			ft_error(cmd, "Error forking", NULL);
		else
			wait(NULL);
		free(path);
	}
}

void	executing(t_cmd **cmd, char *envp[])
{
	//print_cmd_list(cmd);
	check_cmd(cmd, envp);
}
