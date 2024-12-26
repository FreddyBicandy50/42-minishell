/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:36:26 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/27 00:45:05 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void ft_append_command(t_cmd **cmd,t_cmd *new_cmd)
{
	t_cmd *current;

	if (*cmd == NULL)
		*cmd = new_cmd;
	else
	{
		current = *cmd;
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
	}
}
