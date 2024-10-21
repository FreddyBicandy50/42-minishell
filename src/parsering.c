/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/21 17:54:17 by amokdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_cmd *cmd, char *envp[])
{
	char	*path;
	pid_t	pid;

	if (built_in_functions(cmd, envp) == 1)
	{
		path = find_path(cmd->command, envp);
		if (!path)
			return (perror("Error: command not found"));
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, cmd->arg, envp) == -1)
			{
				perror("Error executing command");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid < 0)
			perror("Error forking");
		else
			wait(NULL);
		free(path);
	}
}

void	parser(t_cmd *cmd, char *envp[])
{
	print_cmd_list(cmd);
	check_cmd(cmd, envp);
}
