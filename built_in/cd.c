/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:49:16 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/20 23:46:56 by amokdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

//we want to make a our function named setenv to set env 
void	update_pwd(t_cmd **cmd)
{
	char *new_pwd;
	
	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL)
	{
		 if ((*cmd)->pwd == NULL)
			(*cmd)->pwd = new_pwd;
		else
			(*cmd)->pwd = new_pwd;
		if (setenv("PWD", new_pwd, 1) == -1)
			perror("bash: cd: setenv failed");
	}
	else
		perror("bash: cd: getcwd failed");
}

void	cd_cmd(t_cmd **cmd)
{
	if ((*cmd)->arg == NULL || (*cmd)->arg[0] == NULL)
		chdir(getenv("HOME"));
	else if (chdir((*cmd)->arg[0]) == -1)
		perror("bash: cd");
	update_pwd(cmd);
}
