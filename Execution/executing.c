/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2025/03/19 14:42:50 by marvin           ###   ########.fr       */
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

void check_cmd(t_cmd **cmd, char *envp[])
{
	char *path;
	pid_t pid;

	pid = fork();
	if (pid == 0)
		handle_redirection(*cmd);
	if (built_in_functions(cmd, envp) == 1)
	{
		path = find_path((*cmd)->command, envp);
		if (!path)
			return;
		
		if (pid == 0)
			execute(path, cmd, envp);
		else if (pid < 0)
			ft_error(cmd, "Error forking", NULL);
		else
			wait(NULL);
		free(path);
	}
	if ((*cmd)->redirections != NULL)
		restore_std(*cmd);
}

void executing(t_cmd **cmd, char *envp[])
{
	check_cmd(cmd, envp);
}
