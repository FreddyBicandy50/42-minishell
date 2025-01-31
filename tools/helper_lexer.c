/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:00:19 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/31 23:05:39 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void add_first_cmd(t_cmd **cmd, char *argument)
{
	(*cmd)->arg = malloc(sizeof(char *) * 2);
	if (!(*cmd)->arg)
		free(argument);
	(*cmd)->arg[0] = argument;
	(*cmd)->arg[1] = NULL;
	(*cmd)->arg_number = 1;
}

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

/*
	@EXAMPLE -ARG1 -FLAG2 -ARG2 > Filename

	check if the command is echo everything after we specify a flag is consider args
	except for redirections

	ELSE:then
		skip to the first space
		calc len word skiped
		copy without quotes
		update list of commands arguments
*/
int copy_args(t_cmd **cmd, char *prompt)
{
	int i;
	int len;
	char *argument;

	len = 0;
	if (ft_strncmp((*cmd)->command, "echo", 4) == 0)
		while (prompt[i] != '\0') // you have to check for rirections also and make  a condition for echo to expand the arg after the filename > filename (rest string arg to echo)
			i++;
	else
	{
		argument = skip_to_c(prompt, ' ');
		len = argument - prompt;
		argument = dequotencpy(0, len, prompt);
		if (*argument == '\0')
			free(argument);
		else
		{
			printf("\nArgument[%d]=%s\nargument len=%d", (*cmd)->arg_number, argument, len);
			struct_update_args(cmd, argument);
		}
	}
	return (len);
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