/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:00:19 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/09 15:17:03 by fbicandy         ###   ########.fr       */
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

int update_flags(t_cmd **cmd, int i, char *prompt, char *all_flags)
{
	char *tmp;
	char *flag;
	int j;

	while (printable(prompt[i]) && (prompt[i] != '\0' && prompt[i] != ' '))
		if (pipe_redirections(&prompt[i++], NULL) > 0)
			break;
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
		// Stop processing if redirection was detected
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

	// Check if this is the first redirection for the command
	if (!(*cmd)->redirections)
	{
		(*cmd)->redirections = new_redir;
	}
	else
	{
		t_redir *temp = (*cmd)->redirections;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new_redir;
	}
}

// int handle_pipe_redirection(t_cmd **cmd, char *prompt)
// {
// 	int i = 0;
// 	char redirection = prompt[0];

// 	// Identify consecutive redirection symbols
// 	while ((prompt[i] == '>' || prompt[i] == '<') && prompt[i] != '\0')
// 	{
// 		if (prompt[i] != redirection)
// 		{
// 			printf("Error: parse error near `%c`\n", prompt[i]);
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}

// 	// Set the redirection type
// 	int type = 0;
// 	if (redirection == '>' && i == 2)
// 		type = 2; // >>
// 	else if (redirection == '>' && i == 1)
// 		type = 1; // >
// 	else if (redirection == '<' && i == 2)
// 		type = 3; // <<
// 	else if (redirection == '<' && i == 1)
// 		type = 4; // <

// 	// Obtain the filename following the redirection
// 	prompt = get_last_word(cmd, skip_spaces(prompt + i));
// 	printf("filename=%s\n", (*cmd)->filename);
// 	exit(0);
// 	// Append the redirection to the command's list
// 	append_redirection(cmd, type, ft_strdup((*cmd)->filename)); // Duplicate filename to avoid pointer issues

// 	// Check if additional redirections exist
// 	if (*prompt != '\0')
// 		handle_pipe_redirection(cmd, prompt);

// 	return -1;
// }

int handle_pipe_redirection(t_cmd **cmd, char *prompt)
{
	int i;
	char *new_prompt;

	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);
		i = 0;

		if (prompt[i] == '>' || prompt[i] == '<')
		{
			i++;
			prompt = get_last_word(cmd, prompt + i);
		}
		else
		{
			new_prompt = get_args(cmd, i, prompt);
			if (!new_prompt)
				break;
			prompt = new_prompt;
		}
	}

	return prompt;
}