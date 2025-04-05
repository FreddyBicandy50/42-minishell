/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/05 16:02:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"./../minishell.h"

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

void	execute_command(t_cmd **cmd,char **envp)
{
	int		pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		handle_redirection(*cmd);
		path = find_path((*cmd)->command, envp);
			if (path)
			{
				execute(path, cmd, envp);
				free(path);
			}
			else
				perror("Command not found");
			exit(0);
	}
}

int	check_cmd(t_cmd **cmd, char *envp[])
{
	handle_redirection(*cmd);
	if (built_in_functions(cmd, envp))
		;
	else
		execute_command(cmd,envp);
	return(1);
}

void	handle_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		exit(1);
	}
}

void	handle_wait_status()
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

void close_file( int fd[2], t_fd *f)
{
    if (fd[0] != -1)
        close(fd[0]);
    if (fd[1] != -1)
        close(fd[1]);
    if (f->fd_1 != STDIN_FILENO)
        close(f->fd_1);
    if (f->fd_2 != STDOUT_FILENO)
        close(f->fd_2);
}

void	handle_dup2(t_fd ff)
{
	dup2(ff.fd_1, STDIN_FILENO);
	dup2(ff.fd_2, STDOUT_FILENO);
}

void	simple_execution(t_cmd **cmd, char *envp[])
{
	char	*path;
	pid_t	pid;
	int		check_builtins;
	t_fd	ff;

	ff = handle_redirection(*cmd);
	pid = fork();
	if (pid == 0)
	{
		handle_dup2(ff);
		check_builtins = built_in_functions(cmd, envp);
		if(check_builtins)
		{
			path = find_path((*cmd)->command, envp);
			if (!path)
				exit(1);
			execute(path, cmd, envp);
			free(path);
		}
		exit(0);
	}
	else
	{
		int status;
        if (wait(&status) == -1)
        {
            perror("Wait failed");
            exit(1);  // Exit with error code if waiting fails
        }

        // Check for child process exit status
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            fprintf(stderr, "Child process failed with status %d\n", WEXITSTATUS(status));
        }
	}
}

void	executing(t_cmd **cmd, char *envp[])
{
	t_fd	f;
	int		fd[2];

	if ((*cmd)->next == NULL)
		simple_execution(cmd, envp);
	handle_wait_status();
	return ;
	f.fd_1 = STDIN_FILENO;
	while (*cmd)
	{
		if((*cmd)->next)
			pipe(fd);
		f.fd_2 = STDOUT_FILENO;
		if (check_cmd(cmd, envp) != 1)
		{
			cmd = &(*cmd)->next;
			continue ;
		}
		close_file(fd, &f);
		cmd = &(*cmd)->next;
	}
	if (f.fd_1 != STDIN_FILENO)
		close(f.fd_1);
	handle_wait_status();
}
// void	executing(t_cmd **cmd, char *envp[])
// {
// 	int		pipe_fd[2];
// 	t_fd	f;
	// int		saved_fd;
	// int		flag;

	// f.fd_1 = STDIN_FILENO;
	// while (*cmd != NULL)
	// {
	// 	if ((*cmd)->next)
	// 		pipe(pipe_fd);
	// 	f.fd_2 = STDOUT_FILENO;
	// 	if (check_cmd(cmd, envp, pipe_fd))
	// 	{
	// 		cmd = &(*cmd)->next;
	// 		continue ;
	// 	}
	// 	if ((*cmd)->next)
	// 	{
	// 		close(pipe_fd[1]);
	// 		f.fd_1 = pipe_fd[0];
	// 	}
	// 	cmd = &(*cmd)->next;
	// }
	// if (f.fd_1 != STDIN_FILENO)
	// 	close(f.fd_1);
	// wait_for_children();
	
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
// }