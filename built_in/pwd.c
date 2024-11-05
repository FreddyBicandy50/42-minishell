/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:40:18 by amokdad           #+#    #+#             */
/*   Updated: 2024/11/01 19:57:12 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	pwd_cmd(t_cmd *cmd, char **envp)
{
	int		i;
	char	**pwd;

	(void)cmd;
	i = 0;
	while (ft_strncmp(envp[i], "PWD", 3) == 0)
		i++;
	pwd = ft_split(envp[i] + 4, '=');
	printf("%s\n", pwd[0]);
	free_split(pwd);
	return ;
}
