/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:37:16 by amokdad           #+#    #+#             */
/*   Updated: 2024/10/13 14:10:13 by amokdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd_if_in(t_cmd cmd)
{
	if (ft_strcmp(cmd.command, "echo") == 0)
		printf("\necho //\n");
	else if (ft_strcmp(cmd.command, "cd") == 0)
		printf("\ncd\n");
	else if (ft_strcmp(cmd.command, "pwd") == 0)
		printf("\npwd\n");
	else if (ft_strcmp(cmd.command, "export") == 0)
		printf("\nexport\n");
	else if (ft_strcmp(cmd.command, "unset") == 0)
		printf("\nunset\n");
	else if (ft_strcmp(cmd.command, "env") == 0)
		printf("\nenv\n");
	else if (ft_strcmp(cmd.command, "exit") == 0)
		printf("\nexit\n");
	else
		printf("\ngo to pipes");
}
