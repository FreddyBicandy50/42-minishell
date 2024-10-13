/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:45:30 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/13 17:28:39 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

t_cmd *ft_cmd_lst_new(char *command)
{
	t_cmd *new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->command = command;
	new_cmd->arg = NULL;  // Initialize to NULL
	new_cmd->flag = NULL; // Initialize to NULL
	new_cmd->next = NULL;
	return (new_cmd);
}

void ft_cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd *temp;

	if (!new || !lst)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void free_cmd(t_cmd *cmd)
{
	t_cmd *temp;

	temp = cmd;
	while (temp != NULL)
	{
		free(temp->command);
		free(temp->flag);
		free(temp->arg);
		temp = temp->next;
	}
	free(cmd);
}

void print_cmd_list(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->command)
			printf("Command:%s\n", cmd->command);
		if (cmd->flag)
			printf("Flag:%s\n", cmd->flag);

		if (cmd->arg)
		{
			int i = 0;
			while (cmd->arg[i] != NULL) // Loop through all arguments
			{
				printf("Argument[%d]: %s\n", i, cmd->arg[i]);
				i++;
			}
		}

		cmd = cmd->next;
	}
}
