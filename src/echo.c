/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:07:17 by amokdad           #+#    #+#             */
/*   Updated: 2024/10/20 16:01:05 by amokdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	// if (cmd->arg == NULL && ft_strcmp(cmd->flag, "-n") == 0)
	// 	return ;
	// else 
	if (cmd->arg == NULL)
	{
		printf("\n");
		return ;
	}
	i = 0;
	while (cmd->arg[i] != NULL)
	{
		j = 0;
		while (cmd->arg[i][j] != '\0')
		{
			printf("%c", cmd->arg[i][j]);
			j++;
		}
		i++;
	}
	// if (ft_strcmp(cmd->flag, "-n") == 0)
	// 	return ;
	printf("\n");
}
