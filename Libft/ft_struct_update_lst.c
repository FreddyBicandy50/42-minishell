/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_update_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:52:08 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/02 00:29:49 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

t_cmd *struct_get_last(t_cmd *cmd)
{
    while (cmd->next != NULL)
        cmd = cmd->next;
    return cmd;
}

void struct_update_flags(t_cmd **cmd, char *flag, char *all_flags)
{
    t_cmd *last;
    char *tmp;
    int j;

    last = struct_get_last(*cmd);
    if (all_flags == NULL)
        all_flags = ft_strjoin("-", flag);
    else
    {
        tmp = ft_strjoin(all_flags, flag);
        free(all_flags);
        all_flags = tmp;
    }
    free(flag);
    last->flag = all_flags;
    j = -1;
    while (last->flag[++j] != '\0')
        if (last->flag[j] == ' ')
            last->flag[j] = last->flag[j + 1];
}

void	struct_update_args(t_cmd **cmd, char *arg)
{
	char	**new_arg;
	int		j;
	int		k;

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

void	struct_update_redirection(t_cmd **cmd, int type, char *filename)
{
	t_redir	*new_redir;
	t_redir	*temp;

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

void	struct_print_list(t_cmd *cmd)
{
	int	i;
	// t_redir	*redir;

	//(void)*redir;
	printf("\n\t***ENTERING PRINT STRUCT***\n");
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
	printf("***\t LEAVING PRINT STRUCT***\n");
}
