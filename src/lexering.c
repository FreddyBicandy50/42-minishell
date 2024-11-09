/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/09 14:33:57 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_next_str(t_cmd **cmd, char *prompt)
{
	int i = 0;
	int quote_flag = 0;
	char *command = NULL;

	while (prompt[i] != '\0')
	{
		quote_flag = check_quote(prompt[i], quote_flag);
		if ((ft_strncmp((*cmd)->command, "echo", 4) != 0 && prompt[i] == ' ' && quote_flag == 0) ||
			(prompt[i] == '>' || prompt[i] == '<'))
			break;
		i++;
	}
	if (prompt[0] == 32 || prompt[0] == '\0')
		return 0;
	if (prompt[i] == '>' || prompt[i] == '<')
	{
		printf("Redirection detected\n");
		return handle_pipe_redirection(cmd, prompt + i);
 	}
	command = ft_strncpy(0, i, prompt);
	append_cmd(cmd, command);

	return (i);
}

char *get_next_flag(t_cmd **cmd, char *prompt)
{
	int i;
	char *new_prompt;

	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);
		i = 0;

		if (prompt[i] == '-')
		{
			i++;
			prompt += update_flags(cmd, i, prompt, (*cmd)->flag);
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

char *get_next_command(t_cmd **cmd, char *prompt)
{
	int i;
	char *command;
	t_cmd *new_cmd;
	t_cmd *current;

	prompt = skip_spaces(prompt);
	i = 0;
	if (prompt[i] == '\0')
		return (prompt);
	while (prompt[i] != '\0' && printable(prompt[i]))
		i++;
	command = ft_strncpy(0, i, prompt);
	new_cmd = ft_cmd_lst_new(command);
	if (*cmd == NULL)
		*cmd = new_cmd;
	else
	{
		current = *cmd;
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
	}
	if (prompt[i] != '\0')
		prompt = get_next_flag(&new_cmd, (prompt + i) + 1);
	return (prompt + i);
}

t_cmd *lexer(char *input)
{
	char **segments;
	int i;
	t_cmd *cmd;

	if (!input || *input == '\0')
		return (NULL);
	cmd = NULL;
	segments = NULL;
	segments = ft_split(input, '|');
	i = -1;
	while (segments[++i] != NULL)
		get_next_command(&cmd, segments[i]);
	free_split(segments);
	return (cmd);
}
