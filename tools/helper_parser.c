/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:37:16 by amokdad           #+#    #+#             */
/*   Updated: 2024/11/15 17:17:05 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_split(paths), path);
		free(path);
		i++;
	}
	i = -1;
	free_split(paths);
	return (0);
}

int	built_in_functions(t_cmd **cmd, char **envp)
{
	if (ft_strcmp((*cmd)->command, "echo") == 0)
		echo_cmd(cmd);
	else if (ft_strcmp((*cmd)->command, "cd") == 0)
		printf("\ncd\n");
	else if (ft_strcmp((*cmd)->command, "pwd") == 0)
		pwd_cmd(cmd, envp);
	else if (ft_strcmp((*cmd)->command, "export") == 0)
		printf("\nexport\n");
	else if (ft_strcmp((*cmd)->command, "unset") == 0)
		printf("\nunset\n");
	else if (ft_strcmp((*cmd)->command, "env") == 0)
		printf("\nenv\n");
	else if (ft_strcmp((*cmd)->command, "exit") == 0)
		printf("\nexit\n");
	else
		return (1);
	return (0);
}
