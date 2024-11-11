/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:40:18 by amokdad           #+#    #+#             */
/*   Updated: 2024/11/11 22:32:37 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	pwd_cmd(t_cmd **cmd, char **envp)
{
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PWD", 3) == 0)
		i++;
	(*cmd)->pwd = ft_split(envp[i] + 4, '=');
	printf("%s\n", (*cmd)->pwd[0]);
	free_split((*cmd)->pwd);
	return ;
}
