/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:49:16 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/12 15:16:41 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(t_cmd **cmd, t_env **env)
{
	char	*new_pwd;

	if (!cmd || !(*cmd))
		return ;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL)
	{
		set_env("PWD", new_pwd, env);
		free(new_pwd);
	}
	else
		ft_error(env, "bash: cd: getcwd failed", 1, false);
}

void	cd_cmd(t_cmd **cmd, t_env **env)
{
	char	*old_pwd;

	if (!cmd || !(*cmd))
		return ;
	old_pwd = getcwd(NULL, 0);
	set_env("OLDPWD", old_pwd, env);
	free(old_pwd);
	if ((*cmd)->arg == NULL || (*cmd)->arg[0] == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
			ft_error(env, "bash: cd: getcwd failed", 1, false);
	}
	else if (chdir((*cmd)->arg[0]) == -1)
		ft_error(env, "error no such file or directiory", 1, false);
	update_pwd(cmd, env);
}
