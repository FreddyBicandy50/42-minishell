/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:38:55 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/03/30 23:25:25 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char *path, t_cmd **cmd, char *envp[])
{
	char	**exec_args;
	int		i;
	int		j;

	j = 0;
	i = 1;
	exec_args = malloc(sizeof(char *) * ((*cmd)->arg_number + 2));
	if (!exec_args)
		exit(1);
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
		perror("Error executing command");
	free(exec_args);
}

int	built_in_functions(t_cmd **cmd, char **envp)
{
	if (ft_strcmp((*cmd)->command, "echo") == 0)
		echo_cmd(cmd);
	else if (ft_strcmp((*cmd)->command, "cd") == 0)
		cd_cmd(cmd, envp);
	else if (ft_strcmp((*cmd)->command, "pwd") == 0)
		pwd_cmd();
	else if (ft_strcmp((*cmd)->command, "export") == 0)
		export_cmd(cmd);
	else if (ft_strcmp((*cmd)->command, "unset") == 0)
		unset_cmd(cmd, envp);
	else if (ft_strcmp((*cmd)->command, "env") == 0)
		env_cmd(envp);
	else if (ft_strcmp((*cmd)->command, "exit") == 0)
		exit_minishell();
	else
		return (1);
	return (0);
}

void	handle_pipe(t_cmd **cmd, int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		exit(1);
	}
}

void	handle_redirection(t_cmd **cmd, int *pipe_fd)
{
	if ((*cmd)->next != NULL)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	handle_input_redirection(t_cmd **cmd)
{
	int	fd;

	if ((*cmd)->redir->type == 1)
	{
		fd = open((*cmd)->redir->filename, O_RDONLY);
		if (fd == -1)
		{
			perror("Input redirection failed");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	execute_command(t_cmd **cmd, char **envp, int *pipe_fd)
{
	int		pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		handle_input_redirection(cmd);
		handle_redirection(cmd, pipe_fd);
		if (built_in_functions(cmd, envp) == 1)
		{
			path = find_path((*cmd)->command, envp);
			if (path)
			{
				execute(path, cmd, envp);
				free(path);
			}
			else
				perror("Command not found");
		}
		exit(0);
	}
	else if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
}

void	wait_for_children(void)
{
	int	status;

	while (wait(&status) > 0)
		;
}

void	parser(t_cmd **cmd, char **envp)
{
	int	pipe_fd[2];

	while (*cmd != NULL)
	{
		if ((*cmd)->next != NULL)
			handle_pipe(cmd, pipe_fd);
		execute_command(cmd, envp, pipe_fd);
		if ((*cmd)->next != NULL)
		{
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		cmd = &(*cmd)->next;
	}
	wait_for_children();
}
