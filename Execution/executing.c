/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/01 21:14:06 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

typedef struct s_fd
{
	int	fd_1;
	int	fd_2;
}	t_fd;

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
		perror("Error executing command");
	free(exec_args);
}

void	handle_redirection_betwen_pipe(t_cmd **cmd, int *pipe_fd)
{
	if ((*cmd)->next != NULL)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

int	check_cmd(t_cmd **cmd, char *envp[], int pipe_fd[2])
{
	char	*path;
	pid_t	pid;

	handle_redirection(*cmd);
	pid = fork();
	if (pid == 0)
	{
		handle_redirection_betwen_pipe(cmd, pipe_fd);
		handle_redirection(*cmd);
		if (built_in_functions(cmd, envp) == 1)
		{
			path = find_path((*cmd)->command, envp);
			if (!path)
				exit(1);
			execute(path, cmd, envp);
			free(path);
			return(0) ;
		}
		exit(0);
	}
	else
	{
		wait (NULL);
		if ((*cmd)->redirections != NULL)
			restore_std(*cmd);
	}
	return(1) ;
}

void	handle_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		exit(1);
	}
}

void	wait_for_children(void)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
		{
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		}
	}
}

void	executing(t_cmd **cmd, char *envp[])
{
	int		pipe_fd[2];
	t_fd	f;
	// int		saved_fd;
	// int		flag;

	f.fd_1 = STDIN_FILENO;
	while (*cmd != NULL)
	{
		if ((*cmd)->next)
			pipe(pipe_fd);
		f.fd_2 = STDOUT_FILENO;
		if (check_cmd(cmd, envp, pipe_fd))
		{
			cmd = &(*cmd)->next;
			continue ;
		}
		if ((*cmd)->next)
		{
			close(pipe_fd[1]);
			f.fd_1 = pipe_fd[0];
		}
		cmd = &(*cmd)->next;
	}
	if (f.fd_1 != STDIN_FILENO)
		close(f.fd_1);
	wait_for_children();
	
	// flag = 0;
	// while (*cmd != NULL)
	// {
	// 	if (flag)
	// 		saved_fd = pipe_fd[0];
	// 	if ((*cmd)->next != NULL)
	// 		handle_pipe(pipe_fd);
	// 	check_cmd(cmd, envp, pipe_fd);
	// 	if ((*cmd)->next != NULL)
	// 	{
	// 		if (flag == 0)
	// 			dup2(pipe_fd[0], STDIN_FILENO);
	// 		dup2(saved_fd, STDIN_FILENO);
	// 		close(pipe_fd[0]);
	// 		close(pipe_fd[1]);
	// 	}
	// 	cmd = &(*cmd)->next;
	// }
	// wait_for_children();
}
