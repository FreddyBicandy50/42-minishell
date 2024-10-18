/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/18 09:55:19 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO ALI : check command
#include "minishell.h"

int	check_cmd(t_cmd *cmd)
{
	(void) *cmd;
	return (0);
}

void	parser(t_cmd *cmd)
{
	(void) *cmd;
	print_cmd_list(cmd);
	check_cmd(cmd);
}
