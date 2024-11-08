/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:40:18 by amokdad           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/08 13:15:42 by amokdad          ###   ########.fr       */
=======
/*   Updated: 2024/11/01 19:57:12 by fredybicand      ###   ########.fr       */
>>>>>>> 3027b86a02b950b0a9d079d35fec5f1ceea59e1d
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	pwd_cmd(t_cmd *cmd, char **envp)
{
	int		i;

	(void)cmd;
	i = 0;
	while (ft_strncmp(envp[i], "PWD", 3) == 0)
		i++;
	cmd->pwd = ft_split(envp[i] + 4, '=');
	printf("%s\n", cmd->pwd[0]);
	free_split(cmd->pwd);
	return ;
}
