/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:46:22 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/20 17:01:34 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_cmd *cmd, char *envp[])
{
	char	*path;

	if (built_in_functions(cmd) == 1)
	{
		path = find_path(cmd->command, envp);
		if (!path)
			perror("Error");
	}
}

void	parser(t_cmd *cmd, char *envp[])
{
	print_cmd_list(cmd);
	check_cmd(cmd, envp);
}
