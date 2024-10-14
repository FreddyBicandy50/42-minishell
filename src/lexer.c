/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/14 22:20:25 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_next_str(t_cmd **cmd, char *prompt)
{
	int i = 0;
	int j = 0;
	char *command = NULL;
	int quote = 0;

	// Find the end of the argument (space or end of prompt)
	while (prompt[i] != '\0')
	{
		if ((prompt[i] == '"' || prompt[i] == '\'') && quote==0)
			quote = 1;
		else if ((prompt[i] == '"' || prompt[i] == '\'') && quote==1)
			quote = 0;
		if (prompt[i] == 32 && quote==0)
			break;
		i++;
	}
	if (i == 1 && prompt[0] == ' ')
		return (prompt);
	// Allocate and copy the argument
	command = ft_strncpy(0, i, prompt);
	if (!command)
		return (NULL);

	// Append the argument to cmd->arg
	if (!(*cmd)->arg) // If no arguments yet
	{
		(*cmd)->arg = malloc(sizeof(char *) * j + 1); // One argument + NULL
		if (!(*cmd)->arg)
		{
			free(command); // Free if malloc fails
			return NULL;
		}
		(*cmd)->arg[j] = command;
		(*cmd)->arg[j + 1] = NULL;
		(*cmd)->arg_number = j + 1;
	}
	else // If arguments already exist, expand the array
	{
		while ((*cmd)->arg[j] != NULL)
			j++;
		(*cmd)->arg_number = j + 1;

		// Allocate new space for additional argument and NULL terminator
		char **new_arg = malloc(sizeof(char *) * (j + 2));
		if (!new_arg)
		{
			free(command); // Free command if allocation fails
			return NULL;
		}

		// Copy old arguments
		for (int k = 0; k < j; k++)
			new_arg[k] = (*cmd)->arg[k];

		// Add new argument and null-terminate
		new_arg[j] = command;
		new_arg[j + 1] = NULL;

		// Free old arguments array and point to the new one
		free((*cmd)->arg);
		(*cmd)->arg = new_arg;
	}

	return (prompt + i);
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

			if (all_flags == NULL)
				all_flags = ft_strcat("-", flag);
			else
			{
				char *tmp = ft_strcat(all_flags, flag);
				free(all_flags); // Free the old flag string
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
	free_cmd(cmd);
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
