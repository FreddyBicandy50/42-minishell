/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_execute2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:11:17 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/06 16:56:30 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}

pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	handle_child_process(t_cmd **cmd, t_pipe pipe_fd,
			t_env *env, char *envp[])
{
	if ((*cmd)->next != NULL)
	{
		close(pipe_fd.fd[0]);
		if (dup2(pipe_fd.fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd.fd[1]);
	}
	if (pipe_fd.saved_fd != STDIN_FILENO)
	{
		if (dup2(pipe_fd.saved_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd.saved_fd);
	}
	check_cmd(cmd, envp, env);
	exit(EXIT_SUCCESS);
}


void	handle_parent_process(t_pipe *pipe_fd, t_cmd **cmd)
{
	if (pipe_fd->saved_fd != STDIN_FILENO)
		close(pipe_fd->saved_fd);
	if ((*cmd)->next != NULL)
	{
		close(pipe_fd->fd[1]);
		pipe_fd->saved_fd = pipe_fd->fd[0];
	}
}

void	wait_for_children(void)
{
	int	status;

	while (wait(&status) > 0)
		;
}
