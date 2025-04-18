/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_execute5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:42:53 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/18 20:42:53 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increment_shlvl(t_env **env)
{
	char	*shlvl;
	char	*temp;
	char	*pwd;
	int		level;

	pwd = getcwd(NULL, 0);
	set_env("PWD", pwd, env);
	free(pwd);
	temp = get_env_value(*env, "SHLVL");
	if (!temp)
		level = 1;
	else
		level = ft_atoi(temp);
	level++;
	shlvl = temp;
	shlvl = ft_itoa(level);
	set_env("SHLVL", shlvl, env);
	free(temp);
	free(shlvl);
	set_env("_", "_/usr/bin/env", env);
}

void	inside_fork(t_fork pipe, t_env **env, t_cmd **cmd)
{
	char	*path;

	pipe.pid = fork();
	if (pipe.pid == 0)
	{
		path = relative_path(cmd, env);
		if (!path)
			ft_error(env, ft_strjoin((*cmd)->command, ": command not found"),
				127, true);
		handle_dup2(pipe.ff);
		restoresignal();
		execute(path, cmd, env);
		ft_error(env, "", 1, true);
	}
	else
		wait_for_children(pipe.pid, env, cmd);
}
