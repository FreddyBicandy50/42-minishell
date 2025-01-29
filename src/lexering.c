/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/29 22:46:19 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_next_redirection(t_cmd **cmd, char *prompt)
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
			type = type_redirection(redirection, redir_count);
			if (redir_count > 2)
				ft_error(cmd, "Error: parse error near `%c`\n", &redirection);
			prompt = skip_spaces(prompt + redir_count);
			if (*prompt == '\0' || *prompt == '>' || *prompt == '<')
				ft_error(cmd, "Error: parse error near `%c`\n", &redirection);
			prompt = ft_last_word(cmd, type, prompt);
		}
		else
			prompt++;
	}
	return (-1);
}

/*
	get the prompt example
		-> arg1 -Flag1 -arg2 -Flag2 > testfile1 fil2 -Flag3
	if the command is echo
		everything after is a argument no need to recheck for flag
		except a redirection
	else
		loop threw prompt
			skip to space and skip anything inside a spotted quote

*/
int get_next_str(t_cmd **cmd, char *prompt)
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
		// argument = dequotencpy(0, len, prompt);
		printf("\nArgument[%d]=%s\nargument len=%d", (*cmd)->arg_number, argument, len);
	}

	if (prompt[0] == '\0')
		return (0);
	if (prompt[i] == '>' || prompt[i] == '<')
		return (get_next_redirection(cmd, prompt + i));
	argument = dequotencpy(0, len, prompt);
	ft_append_cmd(cmd, argument);
	return (len);
}

/*
	example: -Flag1 -Arg1 -Flag2 -Arg2

	trim spaces at first
	loop in prompt and check each char
		if is -
			copy the flag
		if quote before -
			copy the flag but skip the quote
		else
			get_argument
*/
char *flags_token(t_cmd **cmd, char *prompt)
{
	int i;
	char *new_prompt;

	printf("\nEntering flags_token\n");
	print_cmd_list(*cmd);
	exit(0);
	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);

		i = 0;
		if (prompt[i] == '-')
			prompt += copy_flag(cmd, i + 1, prompt);
		else if (isquote(prompt[i]) && prompt[i + 1] == '-')
			prompt += copy_flag(cmd, i + 2, prompt);
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

/*
	example : ls -Flag1 -Flag2 arg1 arg2 -Flag3 > file1 file2 file3  | cat Grep "test" | sort | wc -l

	take the segments of commands splitted by pipes
	segment[0] -> ls -Flag1 -Flag2 arg1 arg2 -Flag3 > file1 file2 file3
		-trim spaces and skip the prompt to the first space
		-calculate how many words skipped
			ls = 2 chars
		-dequote the result and copy it
*/
char *command_token(t_cmd **cmd, char *prompt)
{
	char *command;
	t_cmd *new_cmd;
	size_t len;

	printf("\nentering-> command_token\n");
	prompt = skip_spaces(prompt);
	if (prompt[0] == '\0')
		return (prompt);
	// check if first this is a redirection

	len = 0;
	command = skip_to_c(prompt, ' ');
	len = command - prompt;
	command = dequotencpy(0, len, prompt);

	printf("command token extracted =%s\n", command);
	new_cmd = struct_create_list(command);
	struct_addback_list(cmd, new_cmd);
	printf("sturct list created & updated successfuly\n");
	
	print_cmd_list(*(cmd));
	//continue here 
	//TODO fix the flags 
		// Make sure you recieve the cmd well
		// copy the flags 
		// Jump to arguments and do the same
	exit(0);
	if (prompt[len] != '\0')
		prompt = flags_token(cmd, (prompt + len) + 1);
	printf("leaving<- command_token\n\n");
	return (prompt + len);
}

void tokenization(t_cmd **cmd, char *prompt)
{
	command_token(cmd, prompt);
	return;
	flags_token(cmd, prompt);
}