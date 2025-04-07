/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/07 19:05:43 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	execute_command(t_cmd **cmd, char **envp)
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

void	handle_dup2(t_fd ff)
{
	if (ff.fd_1 != STDIN_FILENO)
		dup2(ff.fd_1, STDIN_FILENO);
	if (ff.fd_2 != STDOUT_FILENO)
		dup2(ff.fd_2, STDOUT_FILENO);
}

void	check_cmd(t_cmd **cmd, char *envp[], t_env **env)
{
	pid_t	pid;
	int		check_builtins;
	t_fd	ff;
	char	*path;

	ff = handle_redirection(*cmd);
	pid = fork();
	if (pid == 0)
	{
		handle_dup2(ff);
		check_builtins = built_in_functions(cmd, envp, env);
		if (check_builtins)
		{
			path = find_path((*cmd)->command, envp);
			execute(path, cmd, envp);
		}
		exit(0);
	}
	else
		wait(NULL);
}

void	execute_simple_cmd(t_cmd **cmd, char *envp[], t_env **env)
{
	pid_t	pid;
	t_fd	ff;
	t_fd	original_fds;
	int		check_builtins;
	char	*path;

	(void)env;
	if (save_original_fds(&original_fds.fd_1, &original_fds.fd_2) == -1)
		return ;
	ff = handle_redirection(*cmd);
	handle_dup2(ff);
	check_builtins = built_in_functions(cmd, envp, env);
	if (check_builtins)
	{
		pid = fork();
		if (pid == 0)
		{
			path = find_path((*cmd)->command, envp);
			handle_dup2(ff);
			execute(path, cmd, envp);
		}
		else
			wait_for_children();
	}
	restore_original_fds(original_fds.fd_1, original_fds.fd_2);
}


void	executing(t_cmd **cmd, char *envp[], t_env **env)
{
	t_pipe	pipe_fd;
	pid_t	pid;

	if ((*cmd)->next == NULL)
	{
		execute_simple_cmd(cmd, envp, env);
		return ;
	}
	pipe_fd.saved_fd = STDIN_FILENO;
	while (*cmd != NULL)
	{
		if ((*cmd)->next != NULL)
			create_pipe(pipe_fd.fd);
		pid = create_process();
		if (pid == 0)
			handle_child_process(cmd, pipe_fd, env, envp);
		else
			handle_parent_process(&pipe_fd, cmd);
		cmd = &(*cmd)->next;
	}
	wait_for_children();
}
