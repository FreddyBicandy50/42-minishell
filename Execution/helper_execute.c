/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:48:39 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/12 14:56:26 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_variable(char **envp)
{
	(void)*envp;
	return (0);
}

int	built_in_functions(t_cmd **cmd, t_env **env)
{
	if (ft_strcmp((*cmd)->command, "echo") == 0)
		echo_cmd(cmd);
	else if (ft_strcmp((*cmd)->command, "cd") == 0)
		cd_cmd(cmd, env);
	else if (ft_strcmp((*cmd)->command, "pwd") == 0)
		pwd_cmd();
	else if (ft_strcmp((*cmd)->command, "export") == 0)
		my_export(cmd, env);
	else if (ft_strcmp((*cmd)->command, "unset") == 0)
		my_unset(cmd, env);
	else if (ft_strcmp((*cmd)->command, "env") == 0)
		env_cmd(env);
	else if (ft_strcmp((*cmd)->command, "exit") == 0)
		exit_minishell(cmd, env);
	else
		return (1);
	return (0);
}
