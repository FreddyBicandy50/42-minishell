/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:49:16 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/31 13:19:16 by amokdad          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../src/minishell.h"

// static void	update_pwd_value(int i, const char *new_pwd, char **envp)
// {
// 	size_t	new_len;

// 	new_len = strlen("PWD=") + strlen(new_pwd) + 1;
// 	envp[i] = (char *)malloc(new_len);
// 	if (envp[i] == NULL)
// 	{
// 		perror("malloc");
// 		return ;
// 	}
// 	ft_strlcpy(envp[i], "PWD=", sizeof("PWD="));
// 	ft_stralicat(envp[i], new_pwd);
// }

// static void	set_new_pwd_at_env(const char *new_pwd, char **envp)
// {
// 	int		i;
// 	size_t	len;

// 	len = strlen("PWD=");
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PWD=", len) == 0)
// 		{
// 			update_pwd_value(i, new_pwd, envp);
// 			return ;
// 		}
// 		i++;
// 	}
// 	update_pwd_value(i, new_pwd, envp);
// 	envp[i + 1] = NULL;
// }

void	update_pwd(t_cmd **cmd, char **envp)
{
	char	*new_pwd;

	if (!cmd || !(*cmd))
		return ;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL)
	{
		// set_new_pwd_at_env(new_pwd, envp);
		set_env("PWD=", new_pwd, envp);
		free(new_pwd);
	}
	else
		perror("bash: cd: getcwd failed");
}

void	cd_cmd(t_cmd **cmd, char **envp)
{
	char	*old_pwd;

	if (!cmd || !(*cmd))
		return ;
	old_pwd = getcwd(NULL, 0);
	set_env("OLDPWD=", old_pwd, envp);
	free(old_pwd);
	if ((*cmd)->arg == NULL || (*cmd)->arg[0] == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
			perror("bash: cd: ");
	}
	else if (chdir((*cmd)->arg[0]) == -1)
		perror("bash: cd");
	update_pwd(cmd, envp);
}
