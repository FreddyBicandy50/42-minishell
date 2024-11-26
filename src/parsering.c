/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/26 11:30:29 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute_with_flags(char *path, t_cmd **cmd, char *envp[])
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
		ft_error(cmd, "Error executing command", NULL);
	free(exec_args);
}

void	check_cmd(t_cmd **cmd, char *envp[])
{
	char	*path;
	pid_t	pid;

	if (built_in_functions(cmd, envp) == 1)
	{
		path = find_path((*cmd)->command, envp);
		if (!path)
			return (ft_error(cmd, "command not found:", (*cmd)->command));
		pid = fork();
		if (pid == 0)
		{
			if ((*cmd)->flag == NULL || *(*cmd)->flag == '\0')
			{
				if (execve(path, (*cmd)->arg, envp) == -1)
					ft_error(cmd, "command not found:", (*cmd)->command);
			}
			else
				excute_with_flags(path, cmd, envp);
		}
		else if (pid < 0)
			ft_error(cmd, "Error forking", NULL);
		else
			wait(NULL);
		free(path);
	}
}

void	parser(t_cmd **cmd, char *envp[])
{
	print_cmd_list(*cmd);
	check_cmd(cmd, envp);
}
