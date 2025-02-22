/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/20 21:15:25 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute(char *path, t_cmd **cmd, char *envp[])
{
	char **exec_args;
	int i;
	int j;

	// FIX THIS INVALID WRITE OF SIZE 8
	/*
		==13894== Invalid write of size 8
==13894==    at 0x10A666: execute (executing.c:34)
==13894==    by 0x10A741: check_cmd (executing.c:57)
==13894==    by 0x10A7A8: executing (executing.c:69)
==13894==    by 0x1096B9: main (main.c:113)
==13894==  Address 0x4b7a068 is 0 bytes after a block of size 40 alloc'd
==13894==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==13894==    by 0x10A5A8: execute (executing.c:23)
==13894==    by 0x10A741: check_cmd (executing.c:57)
==13894==    by 0x10A7A8: executing (executing.c:69)
==13894==    by 0x1096B9: main (main.c:113)
==13894==
	*/
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
	// pid_t pid;

	path = find_path((*cmd)->command, envp);
	if (!path)
		return;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	// handle_redirection(*cmd);
	// 	execute(path, cmd, envp);
	// }
	// else if (pid < 0)
	// 	ft_error(cmd, "Error forking", NULL);
	// else
	// 	wait(NULL);
	free(path);
	// if (built_in_functions(cmd, envp) == 1)
	// {

	// }
}

void executing(t_cmd **cmd, char *envp[])
{
	check_cmd(cmd, envp);
}
