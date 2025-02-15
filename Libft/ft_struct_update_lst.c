/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_update_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:52:08 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/11 12:07:39 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

t_cmd *struct_get_first(t_cmd *cmd)
{
	printf("**ENTRING struct_get_first(t_cmd *cmd) in Libft/ft_struct_update_lst.c**\n");
	while (cmd->prev != NULL)
	{
		printf("going backwards CMD->command=%s\n", cmd->command);
		cmd = cmd->prev;
	}
	printf("Lastone CMD->command=%s\n", cmd->command);
	printf("**LEAVING struct_get_first**\n");
	return cmd;
}

void struct_update_flags(t_cmd **cmd, char *flag, char *all_flags)
{
	char *tmp;
	int j;

	if (all_flags == NULL)
		all_flags = ft_strjoin("-", flag);
	else
	{
		tmp = ft_strjoin(all_flags, flag);
		free(all_flags);
		all_flags = tmp;
	}
	free(flag);
	(*cmd)->flag = all_flags;
	j = -1;
	while ((*cmd)->flag[++j] != '\0')
		if ((*cmd)->flag[j] == ' ')
			(*cmd)->flag[j] = (*cmd)->flag[j + 1];
}

void struct_update_args(t_cmd **cmd, char *arg)
{
	char **new_arg;
	int j;
	int k;

	j = 0;
	k = -1;
	if (!(*cmd)->arg)
		struct_add_first_cmd(cmd, arg);
	else
	{
		while ((*cmd)->arg[j] != NULL)
			j++;
		(*cmd)->arg_number = j + 1;
		new_arg = malloc(sizeof(char *) * (j + 2));
		while (k++ < j)
			new_arg[k] = (*cmd)->arg[k];
		new_arg[j] = arg;
		new_arg[j + 1] = NULL;
		free((*cmd)->arg);
		(*cmd)->arg = new_arg;
	}
}

void struct_update_redirection(t_cmd **cmd, int type, char *filename)
{
	t_redir *new_redir;
	t_redir *temp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		ft_error(cmd, "malloc failed", NULL);
	new_redir->type = type;
	new_redir->filename = filename;
	new_redir->next = NULL;
	if (!(*cmd)->redirections)
		(*cmd)->redirections = new_redir;
	else
	{
		temp = (*cmd)->redirections;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

void struct_print_list(t_cmd *cmd)
{
	int i;
	t_redir *redirections;

	printf("**ENTERING struct_print_list(t_cmd *cmd)**\n");
	if (cmd == NULL)
		printf("\tstruct is empty\n");
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
		redirections = cmd->redirections;
		while (redirections != NULL)
		{
			if (redirections->type == 4)
				printf("\tRedirection of type: >>\n");
			if (redirections->type == 3)
				printf("\tRedirection of type: <<\n");
			if (redirections->type == 2)
				printf("\tRedirection of type: >\n");
			if (redirections->type == 1)
				printf("\tRedirection of type: <\n");
			printf("\tFilename: %s\n\n", redirections->filename);
			redirections = redirections->next;
		}
		cmd = cmd->next;
	}
	printf("**LEAVING struct_print_list(t_cmd *cmd)**\n");
}
