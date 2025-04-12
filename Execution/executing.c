/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/12 15:58:13 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	handle_dup2(t_fd ff)
{
	if (ff.fd_1 != STDIN_FILENO)
		dup2(ff.fd_1, STDIN_FILENO);
	if (ff.fd_2 != STDOUT_FILENO)
		dup2(ff.fd_2, STDOUT_FILENO);
}

void	check_cmd(t_cmd **cmd, t_env **env)
{
	pid_t	pid;
	int		check_builtins;
	t_fd	ff;
	char	*path;

	ff = handle_redirection(env, *cmd);
	pid = fork();
	if (pid == 0)
	{
		handle_dup2(ff);
		check_builtins = built_in_functions(cmd, env);
		if (check_builtins)
		{
			path = find_path((*cmd)->command, env);
			if (!path)
				ft_error(env, ft_strjoin((*cmd)->command, "command not found"),
					127, true);
			execute(path, cmd, env);
		}
		ft_error(env, "", 1, true);
	}
	else
		wait_for_children(pid, env);
}

void	execute_simple_cmd(t_cmd **cmd, t_env **env)
{
	t_fork	pipe;
	int		check_builtins;

	if (save_original_fds(&pipe.original_fds.fd_1, &pipe.original_fds.fd_2,
			env) == -1)
		return ;
	pipe.ff = handle_redirection(env,*cmd);
	handle_dup2(pipe.ff);
	check_builtins = built_in_functions(cmd, env);
	if (check_builtins)
		inside_fork(pipe, env, cmd);
	restore_original_fds(pipe.original_fds.fd_1, pipe.original_fds.fd_2, env);
}

void	executing(t_cmd **cmd, t_env **env)
{
	t_pipe	pipe_fd;
	pid_t	pid;

	if ((*cmd)->next == NULL)
	{
		execute_simple_cmd(cmd, env);
		return ;
	}
	pipe_fd.saved_fd = dup(STDIN_FILENO);
	while (*cmd != NULL)
	{
		if ((*cmd)->next != NULL)
			create_pipe(env, pipe_fd.fd);
		pid = create_process(env);
		if (pid == 0)
			handle_child_process(cmd, pipe_fd, env);
		else
			handle_parent_process(&pipe_fd, cmd);
		cmd = &(*cmd)->next;
	}
	wait_for_children(pid, env);
}
