/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:00:19 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/09 13:03:34 by fbicandy         ###   ########.fr       */
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

int handle_pipe_redirection(t_cmd **cmd, char *prompt)
{
	int i = 0;
	char redirection = prompt[0]; // Initialize with first redirection character

	// Identify consecutive redirection symbols and confirm valid type
	while ((prompt[i] == '>' || prompt[i] == '<') && prompt[i] != '\0')
	{
		if (prompt[i] != redirection) // Check for mismatched symbols (e.g., "><")
		{
			printf("Error: parse error near `%c`\n", prompt[i]);
			exit(1);
		}
		i++;
	}

	// Determine redirection type based on symbol and count
	if (redirection == '>' && i == 2)
		(*cmd)->redirect = 2; // >>
	else if (redirection == '>' && i == 1)
		(*cmd)->redirect = 1; // >
	else if (redirection == '<' && i == 2)
		(*cmd)->redirect = 3; // <<
	else if (redirection == '<' && i == 1)
		(*cmd)->redirect = 4; // <

	prompt = get_last_word(cmd, skip_spaces(prompt + i));
	// Recursively process any additional redirections in the remaining prompt
	if (*prompt != '\0')
		return handle_pipe_redirection(cmd, prompt);
	return -1;
}

