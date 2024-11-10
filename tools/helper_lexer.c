/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:00:19 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/10 11:00:18 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void append_cmd(t_cmd **cmd, char *command)
{
	char **new_arg;
	int j;
	int k;

	j = 0;
	k = -1;
	if (!(*cmd)->arg)
		add_first_cmd(cmd, command);
	else
	{
		while ((*cmd)->arg[j] != NULL)
			j++;
		(*cmd)->arg_number = j + 1;
		new_arg = malloc(sizeof(char *) * (j + 2));
		while (k++ < j)
			new_arg[k] = (*cmd)->arg[k];
		new_arg[j] = command;
		new_arg[j + 1] = NULL;
		free((*cmd)->arg);
		(*cmd)->arg = new_arg;
	}
}
// when you open back write a detailed comments here
int update_flags(t_cmd **cmd, int i, char *prompt, char *all_flags)
{
	char *tmp;
	char *flag;
	int j;

	// block 1
	while (printable(prompt[i]) && (prompt[i] != '\0' && prompt[i] != ' '))
		if (prompt[i] == '>' || prompt[i++] == '<')
			break;
	// block 2
	flag = ft_strncpy(1, i, prompt);
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
	return (i);
}

char *get_args(t_cmd **cmd, int i, char *prompt)
{
	int n = get_next_str(cmd, prompt);

	if (n > 0)
		prompt += n;
	else
	{
		if (prompt[i] == '\0' || n == -1)
			return NULL;
		prompt++;
	}
	return prompt;
}
void append_redirection(t_cmd **cmd, int type, char *filename)
{
	t_redir *new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_redir->type = type;
	new_redir->filename = filename;
	new_redir->next = NULL;
	if (!(*cmd)->redirections)
		(*cmd)->redirections = new_redir;
	else
	{
		t_redir *temp = (*cmd)->redirections;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

int handle_pipe_redirection(t_cmd **cmd, char *prompt)
{
	char redirection;
	int type;
	int redir_count;

	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);
		if (*prompt == '>' || *prompt == '<')
		{
			redirection = *prompt;
			redir_count = 1;
			while (*(prompt + redir_count) == redirection)
				redir_count++;

			if (redir_count > 2)
			{
				printf("Error: parse error near `%c`\n", redirection);
				exit(EXIT_FAILURE);
			}

			// Set the redirection type
			if (redirection == '>' && redir_count == 2)
				type = 2; // >>
			else if (redirection == '>' && redir_count == 1)
				type = 1; // >
			else if (redirection == '<' && redir_count == 2)
				type = 3; // <<
			else if (redirection == '<' && redir_count == 1)
				type = 4; // <

			prompt += redir_count;
			prompt = skip_spaces(prompt);

			// Check for missing filename after redirection
			if (*prompt == '\0' || *prompt == '>' || *prompt == '<')
			{
				printf("Error: missing filename after `%c`\n", redirection);
				exit(EXIT_FAILURE);
			}

			// Retrieve and store the filename, handling quoted filenames
			prompt = ft_last_word(cmd, type, prompt);
		}
		else
			prompt++;
	}
	return -1;
}
