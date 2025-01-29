/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:45:30 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/29 22:45:06 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

t_cmd	*struct_create_list(char *command)
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


/*
	Example : commnad -FLAG1 -Arg1 -Flag2 - Arg2
	After the lexer extract the token 
		if the cmd->args is null

*/
void	ft_append_cmd(t_cmd **cmd, char *Token)
{
	char	**new_arg;
	int		j;
	int		k;

	j = 0;
	k = -1;
	if (!(*cmd)->arg)
		add_first_cmd(cmd, Token);
	else
	{
		while ((*cmd)->arg[j] != NULL)
			j++;
		(*cmd)->arg_number = j + 1;
		new_arg = malloc(sizeof(char *) * (j + 2));
		while (k++ < j)
			new_arg[k] = (*cmd)->arg[k];
		new_arg[j] = Token;
		new_arg[j + 1] = NULL;
		free((*cmd)->arg);
		(*cmd)->arg = new_arg;
	}
}

void	struct_addback_list(t_cmd **lst, t_cmd *new)
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
		// if (temp->redirections)
		// 	free_redirections(temp->redirections);
		cmd = cmd->next;
		free(temp);
	}
}

void	print_cmd_list(t_cmd *cmd)
{
	int	i;
	// t_redir	*redir;

	//(void)*redir;
	printf("\n->Entering print_cmd_list\n");
	while (cmd != NULL)
	{
		if (cmd->command)
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
		// redir = cmd->redirections;
		// while (redir != NULL)
		// {
		// 	printf("Redirection type: %d\n", redir->type);
		// 	if (redir->filename)
		// 		printf("Filename: %s\n", redir->filename);
		// 	redir = redir->next;
		// }
		cmd = cmd->next;
	}
	printf("Leaving<- print_cmd_list\n");
}

void	add_first_cmd(t_cmd **cmd, char *argument)
{
	(*cmd)->arg = malloc(sizeof(char *) * 2);
	if (!(*cmd)->arg)
		free(argument);
	(*cmd)->arg[0] = argument;
	(*cmd)->arg[1] = NULL;
	(*cmd)->arg_number = 1;
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