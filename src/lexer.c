/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/12 23:09:11 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_next_str(t_cmd **cmd, char *prompt)
{
	int i;
	char *arg;
	int in_quotes;
	char quote_type;

	i = 0;
	in_quotes = 0;
	quote_type = '\0';
	prompt = skip_spaces(prompt);
	while (prompt[i] != '\0' && !prd(prompt[i]))
	{
		if (ft_strncmp((*cmd)->command, "echo", 4) != 0 && prompt[i] == ' ')
			break;
		if (prompt[i] == '"' || prompt[i] == '\'')
		{
			if (in_quotes && prompt[i] == quote_type)
				in_quotes = 0;
			else if (!in_quotes)
			{
				in_quotes = 1;
				quote_type = prompt[i];
			}
		}
		else if (!in_quotes && (prd(prompt[i])==1))
			break;
		i++;
	}
	arg = ft_strncpy(0, i, prompt);
	if ((arg[0] == '\'' || arg[0] == '"') && arg[i - 1] == arg[0] && i > 1)
	{
		char *stripped_arg = ft_strsub(arg, 1, i - 2);
		free(arg);
		arg = stripped_arg;
	}

	(*cmd)->arg = arg;
	return prompt += i;
}

char *get_next_flag(t_cmd **cmd, char *prompt)
{
	int i;
	char *flag;
	char *all_flags;

	all_flags = NULL;
	while (*prompt != '\0' && !prd(*prompt))
	{
		prompt = skip_spaces(prompt);
		i = 0;
		if (prompt[i] == '-')
		{
			i++;
			while (printable(prompt[i]) && (prompt[i] != '\0' && prompt[i] != ' '))
			{
				if (prd(prompt[i]))
					break;
				i++;
			}
			flag = ft_strncpy(1, i, prompt);
			char *tmp;
			if (all_flags == NULL)
				all_flags = ft_strcat("-", flag);
			else
			{
				tmp = ft_strcat(all_flags, flag);
				free(all_flags);
				all_flags = tmp;
			}
			free(flag);
			prompt += i;
		}
		else
		{
			prompt = get_next_str(cmd, prompt);
			prompt++;
		}
	}
	(*cmd)->flag = all_flags;
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
	t_cmd *cmd;

	cmd = NULL;
	if (!data->input || *data->input == '\0')
		return;
	data->input = get_next_command(&cmd, data->input);
	if (cmd)
		print_cmd_list(cmd);
}

// 4. Handle Strings and Quoted Sections
// For handling quoted strings:
// If you encounter a ", start capturing the string inside the quotes, treating it as a single token.
// Continue parsing until you find the closing ".
// Ensure you handle both single (') and double (") quotes.
// Edge Case:
// Handle nested quotes carefully and ignore spaces inside quotes.
// Example: echo "hello world" should treat "hello world" as one argument.
// Make sure to handle special cases like echo 'single quotes' "double quotes" correctly.
// 5. Handle Redirections (>, >>, <, <<)
// When you encounter a redirection symbol (>, >>, <, <<):
// Capture the command and arguments up to this point.
// Store the redirection symbol and prepare to handle the next token (which will be the file).
// Implementation:
// On detecting >, >>, <, or <<, save the redirection type and index.
// The next token after the redirection symbol should be a file name or a file descriptor.
// Edge Case:
// Ensure that after each redirection, spaces between the redirection symbol and the file are handled.
// 6. Handle Pipes (|)
// When a pipe (|) is encountered:
// Treat it as a break between two separate commands.
// Implementation:
// Once you hit a pipe, treat everything before it as a separate command.
// Reset your command extraction and start from the next character after the pipe for the next command.
// Edge Case:
// Consecutive pipes (e.g., | |) are invalid and should be flagged.
// 7. Recursive Parsing of Compound Commands
// In cases where there are multiple commands separated by |, redirection symbols, etc., handle each segment individually.
// Implementation:
// When a |, >, < is detected, save the current parsed command.
// Recursively continue parsing from the next point, handling each segment until the end of the input.
// Edge Case:
// Handle consecutive commands properly, ensuring each segment is parsed completely before moving to the next.
// 8. Handle Termination (\0)
// When the end of the input is reached, handle any remaining tokens.
// Ensure that all commands, arguments, and redirections are stored properly in a structured format (like an array or list).
