/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:37:16 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/21 17:54:35 by amokdad          ###   ########.fr       */
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
	(void) envp;
	if (ft_strcmp((*cmd)->command, "echo") == 0)
		echo_cmd(cmd);
	else if (ft_strcmp((*cmd)->command, "cd") == 0)
		cd_cmd(cmd);
	else if (ft_strcmp((*cmd)->command, "pwd") == 0)
		pwd_cmd();
	else if (ft_strcmp((*cmd)->command, "export") == 0)
		printf("\nexport\n");
	else if (ft_strcmp((*cmd)->command, "unset") == 0)
		printf("\nunset\n");
	else if (ft_strcmp((*cmd)->command, "env") == 0)
		env_cmd();
	else if (ft_strcmp((*cmd)->command, "exit") == 0)
		printf("\nexit\n");
	else
		return (1);
	return (0);
}
