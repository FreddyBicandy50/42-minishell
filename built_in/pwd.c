/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:40:18 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/14 11:49:46 by amokdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	pwd_cmd(t_cmd **cmd, char **envp)
{
	(void)envp;
	(*cmd)->pwd = getenv("PWD");
	if ((*cmd)->pwd != NULL)
		printf("%s\n", (*cmd)->pwd);
	else
		printf("PWD environment variable not found.\n");
	return ;
}
