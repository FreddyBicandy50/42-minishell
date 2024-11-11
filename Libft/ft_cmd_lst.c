/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:45:30 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/11 22:22:12 by fredybicand      ###   ########.fr       */
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
	new_cmd->filename = NULL;
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

void	free_redirections(t_redir *redirections)
{
	t_redir	*temp;

	while (redirections != NULL)
	{
		temp = redirections;
		free(temp->filename);
		redirections = redirections->next;
		free(temp);
	}
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
		if (temp->redirections)
			free_redirections(temp->redirections);
		cmd = cmd->next;
		free(temp);
	}
}

void	print_cmd_list(t_cmd *cmd)
{
	int		i;
	t_redir	*redir;

	while (cmd != NULL)
	{
		if (cmd->command)
			printf("Command: %s\n", cmd->command);
		if (cmd->flag)
			printf("Flag: %s\n", cmd->flag);
		if (cmd->arg)
		{
			i = 0;
			while (i < cmd->arg_number)
			{
				if (cmd->arg[i] != NULL)
					printf("Argument[%d]: %s$\n", i, cmd->arg[i]);
				i++;
			}
			printf("Argument count: %d\n", cmd->arg_number);
		}
		redir = cmd->redirections;
		while (redir != NULL)
		{
			printf("Redirection type: %d\n", redir->type);
			if (redir->filename)
				printf("Filename: %s\n", redir->filename);
			redir = redir->next;
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
