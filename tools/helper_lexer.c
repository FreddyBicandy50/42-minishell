/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:00:19 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/29 22:25:37 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void append_cmd(t_cmd **cmd, char *argument)
{
	char **new_arg;
	int j;
	int k;

	j = 0;
	k = -1;
	if (!(*cmd)->arg)
		add_first_cmd(cmd, argument);
	else
	{
		while ((*cmd)->arg[j] != NULL)
			j++;
		(*cmd)->arg_number = j + 1;
		new_arg = malloc(sizeof(char *) * (j + 2));
		while (k++ < j)
			new_arg[k] = (*cmd)->arg[k];
		new_arg[j] = argument;
		new_arg[j + 1] = NULL;
		free((*cmd)->arg);
		(*cmd)->arg = new_arg;
	}
}

void update_flags(t_cmd **cmd, char *flag, char *all_flags)
{
	char	*tmp;
	int		j;

	if (all_flags == NULL)
		all_flags = ft_strcat("-", flag);
	else
	{
		tmp = ft_strcat(all_flags, flag);
		free(all_flags);
		all_flags = tmp;
	}
	free(flag);
	(*cmd)->flag = all_flags;
	j = -1;
	while ((*cmd)->flag[++j] != '\0')
		if ((*cmd)->flag[j] == 32)
			(*cmd)->flag[j] = (*cmd)->flag[j + 1];
}

/*
	get arguments example
		-> arg1 -Flag1 arg2 -Flag2
	// GNS will get the arg from start to end
		-> and get the number of chars found
			if n>0 means i found more than at least 1 char argument
				skip this arg example arg1 = 4
				prompt+=4 is ( -Flag1 ...)
			else
				check didnt catch anything probably its the end of string or
					at least args maybe we now have flag
				return +1 if not empty and null for empty
*/
char *get_args(t_cmd **cmd, int i, char *prompt)
{
	int n;
 
	n = get_next_str(cmd, prompt);
	if (n > 0)
		prompt += n;
	else
	{
		if (prompt[i] == '\0' || n == -1)
			return (NULL);
		prompt++;
	}
	return (prompt);
}

void append_redirection(t_cmd **cmd, int type, char *filename)
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

int type_redirection(char redirection, int redirection_count)
{
	if (redirection == '>' && redirection_count == 2)
		return (2);
	else if (redirection == '>' && redirection_count == 1)
		return (1);
	else if (redirection == '<' && redirection_count == 2)
		return (3);
	else if (redirection == '<' && redirection_count == 1)
		return (4);
	return (0);
}