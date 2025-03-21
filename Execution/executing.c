/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2025/03/21 15:16:48 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void execute(char *path, t_cmd **cmd, char *envp[])
{
	char **exec_args;
	int i;
	int j;

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

void	check_cmd(t_cmd **cmd, char *envp[])
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		handle_redirection(*cmd);
		if (built_in_functions(cmd, envp) == 1)
		{
			path = find_path((*cmd)->command, envp);
			if (!path)
				return ;
			execute(path, cmd, envp);
			free(path);
			return ;
		}
	}
	else
		wait (NULL);
	if ((*cmd)->redirections != NULL)
		restore_std(*cmd);
}

void	executing(t_cmd **cmd, char *envp[])
{
	int		fd[2];
	int		pid;
	t_cmd	*current_cmd;
	int		input_fd;

	current_cmd = *cmd;
	input_fd = 0;
	if ((*cmd)->next == NULL)
		check_cmd(cmd, envp);
	else
	{
		while (current_cmd != NULL)
		{
			if (current_cmd->next != NULL)
			{
				if (pipe(fd) == -1)
				{
					perror("Error creating pipe");
					return ;
				}
			}

			pid = fork();
			if (pid == -1)
			{
				perror("Error forking");
				return ;
			}

			if (pid == 0)
			{
				if (input_fd != 0)
				{
					dup2(input_fd, 0);
					close(input_fd);
				}
				if (current_cmd->next != NULL)
				{
					dup2(fd[1], 1);
					close(fd[1]);
				}
				check_cmd(&current_cmd, envp);
				return ;
			}
			else
			{
				if (current_cmd->next != NULL)
					close(fd[1]);
				input_fd = fd[0];
				current_cmd = current_cmd->next;
				wait (NULL);
			}
		}
	}
}
