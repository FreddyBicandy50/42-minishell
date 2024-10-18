/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/18 12:19:10 by amokdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO ALI : check command
#include "minishell.h"

int	check_cmd(t_cmd *cmd, char *envp[])
{
	check_cmd_if_included(cmd, envp);
	return (0);
}

void	parser(t_cmd *cmd, char *envp[])
{
	(void) *cmd;
	print_cmd_list(cmd);
	check_cmd(cmd, envp);
}
