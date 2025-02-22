/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:45:30 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/22 15:12:55 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

t_cmd *struct_create_list(char *command, t_cmd *new_cmd)
{
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->command = command;
	new_cmd->arg = NULL;
	new_cmd->flag = NULL;
	new_cmd->arg_number = 0;
	new_cmd->next = NULL;
	new_cmd->redirections = NULL;
	// new_cmd->prev = current;
	return (new_cmd);
}

void struct_addback_list(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd *temp;

	temp = NULL;
	if (*cmd == NULL)
	{
		printf("Adding first command\n");
		*cmd = new_cmd;
	}
	else
	{
		temp = *cmd;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_cmd;
	}
}
void struct_add_first_cmd(t_cmd **cmd, char *argument)
{
	(*cmd)->arg = malloc(sizeof(char *) * 2);
	if (!(*cmd)->arg)
		free(argument);
	(*cmd)->arg[0] = argument;
	(*cmd)->arg[1] = NULL;
	(*cmd)->arg_number = 1;
}

void struct_free_redirections(t_redir *redirections)
{
	t_redir *temp;

	while (redirections != NULL)
	{
		temp = redirections;
		free(temp->filename);
		redirections = redirections->next;
		free(temp);
	}
}

void struct_free_cmd(t_cmd *cmd)
{
	t_cmd *temp;

	while (cmd != NULL)
	{
		temp = cmd;
		free(temp->command);
		free(temp->flag);
		if (temp->arg)
			free_split(temp->arg);
		if (temp->redirections)
			struct_free_redirections(temp->redirections);
		cmd = cmd->next;
		free(temp);
	}
}
