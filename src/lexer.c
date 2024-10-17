/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/17 02:12:08 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_next_str(t_cmd **cmd, char *prompt)
{
	int i;
	int quote_flag;
	char *command;

	i = 0;
	quote_flag = 0;
	command = NULL;
	while (prompt[i] != '\0')
	{
		quote_flag = check_quote(prompt[i], quote_flag);
		if (ft_strncmp((*cmd)->command, "echo", 4) != 0 && prompt[i] == 32 && quote_flag == 0)
			break;
		i++;
	}
	if (prompt[0] == 32 || prompt[0] == '\0')
		return (0);
	command = ft_strncpy(0, i, prompt);
	if (!command)
		return (-1);
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
	return (prompt);
}

char *get_next_command(t_cmd **cmd, char *prompt)
{
	int i;
	char *command;

	prompt = skip_spaces(prompt);
	i = 0;
	if (prompt[i] == '\0')
		return (prompt);
	while (prompt[i] != '\0' && printable(prompt[i]))
		i++;
	command = ft_strncpy(0, i, prompt);
	if (!command)
		return (NULL);
	*cmd = ft_cmd_lst_new(command);
	if (!*cmd)
		return (NULL);
	if (!prompt[i] == '\0')
		prompt = get_next_flag(cmd, (prompt + i) + 1);
	return (prompt + i);
}
void lexering(t_data *data)
{
	int index;
	int start;
	int end;
	char *segment;
	t_data *new_data;
	t_data *head = NULL;
	t_data *tail = NULL;

	index = -1;
	start = 0;
	end = -1;

	while (data->input[++index] != '\0')
	{
		if (data->input[index] == '|')
		{
			// Extract the segment before the pipe
			end = index;
			segment = ft_strndup(&data->input[start], end - start);

			// Create a new t_data node and append to the list
			new_data = create_new_data_node(segment);
			if (head == NULL)
			{
				head = new_data;
				tail = new_data;
			}
			else
			{
				append_data_node(&tail, new_data);
				tail = new_data; // Move the tail to the new end of the list
			}

			free(segment);	   // Free the temporary segment string
			start = index + 1; // Move start to the next segment after the pipe
		}
	}

	if (start < index)
	{
		segment = ft_strndup(&data->input[start], index - start);
		new_data = create_new_data_node(segment);

		if (head == NULL)
		{
			head = new_data;
			tail = new_data;
		}
		else
		{
			append_data_node(&tail, new_data);
			tail = new_data; // Move the tail to the new end of the list
		}

		free(segment); // Free the temporary segment string
	}

	t_data *current = head;
	while (current != NULL)
	{
		printf("Segment: %s\n", current->input);
		current = current->next;
	}
}
