/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:45:30 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/18 10:01:24 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

t_cmd	*ft_cmd_lst_new(char *command)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->command = command;
	new_cmd->arg = NULL;
	new_cmd->flag = NULL;
	new_cmd->arg_number = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd != NULL)
	{
		temp = cmd;
		free(temp->command);
		free(temp->flag);
		if (temp->arg)
			free_split(temp->arg);
		cmd = cmd->next;
		free(temp);
	}
}

void	print_cmd_list(t_cmd *cmd)
{
	int	i;

	while (cmd != NULL)
	{
		if (cmd->command)
			printf("Command:%s\n", cmd->command);
		if (cmd->flag)
			printf("Flag:%s\n", cmd->flag);
		if (cmd->arg)
		{
			i = 0;
			while (i < cmd->arg_number)
			{
				if (cmd->arg != NULL)
					printf("Argument[%d]:%s$\n", i, cmd->arg[i]);
				i++;
			}
			printf("n=%d\n", cmd->arg_number);
		}
		cmd = cmd->next;
	}
}

void	add_first_cmd(t_cmd **cmd, char *command)
{
	(*cmd)->arg = malloc(sizeof(char *) * 2);
	if (!(*cmd)->arg)
		free(command);
	(*cmd)->arg[0] = command;
	(*cmd)->arg[1] = NULL;
	(*cmd)->arg_number = 1;
}
