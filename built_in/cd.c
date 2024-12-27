/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:49:16 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/27 16:41:15 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

static void	update_pwd_value(int i, const char *new_pwd)
{
	size_t	new_len;

	new_len = strlen("PWD=") + strlen(new_pwd) + 1;
	environ[i] = (char *)malloc(new_len);
	if (environ[i] == NULL)
	{
		perror("malloc");
		return ;
	}
	ft_strlcpy(environ[i], "PWD=", sizeof("PWD="));
	strcat(environ[i], new_pwd);
}

static void	set_new_pwd_at_env(const char *new_pwd)
{
	int		i;
	size_t	len;

	len = strlen("PWD=");
	i = 0;
	while (environ[i])
	{
		if (strncmp(environ[i], "PWD=", len) == 0)
		{
			update_pwd_value(i, new_pwd);
			return ;
		}
		i++;
	}
	update_pwd_value(i, new_pwd);
	environ[i + 1] = NULL;
}

void	update_pwd(t_cmd **cmd)
{
	char	*new_pwd;

	if (!cmd || !(*cmd))
		return ;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL)
	{
		set_new_pwd_at_env(new_pwd);
		free(new_pwd);
	}
	else
		perror("bash: cd: getcwd failed");
}

void	cd_cmd(t_cmd **cmd)
{
	if (!cmd || !(*cmd))
		return ;
	if ((*cmd)->arg == NULL || (*cmd)->arg[0] == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
			perror("bash: cd: ");
	}
	else if (chdir((*cmd)->arg[0]) == -1)
		perror("bash: cd");
	update_pwd(cmd);
}
