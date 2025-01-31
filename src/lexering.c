/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/31 23:26:41 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_next_redirection(t_cmd **cmd, char *prompt)
{
	char redirection;
	int type;
	int redir_count;

	(void)type;
	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);
		if (*prompt == '>' || *prompt == '<')
		{
			redirection = *prompt;
			redir_count = 1;
			while (*(prompt + redir_count) == redirection)
				redir_count++;
			//type = type_redirection(redirection, redir_count);
			if (redir_count > 2)
				ft_error(cmd, "Error: parse error near `%c`\n", &redirection);
			prompt = skip_spaces(prompt + redir_count);
			if (*prompt == '\0' || *prompt == '>' || *prompt == '<')
				ft_error(cmd, "Error: parse error near `%c`\n", &redirection);
			// prompt = ft_last_word(cmd, type, prompt);
		}
		else
			prompt++;
	}
	return (-1);
}

/*
	@EXAMPLE arg1 -Flag1 arg2 -Flag2
	
	IF arg found skip the number of its characters
	else check if aynithing persist in prompt
	
*/
char *args_token(t_cmd **cmd, int i, char *prompt)
{
	int n;

	n = copy_args(cmd, prompt);
	if (n > 0)
		prompt += n;
	else
	{
		if (prompt[i] == '\0')
			return (NULL);
		prompt++;
	}
	return (prompt);
}

/*
	@EXAMPLE -FLAG1 -ARG1 -FLAG2 -ARG2 etc...

	LOOP (S):
		IF *S (-) OR *S IS (") but *S+1 IS (-):then
			copy all the following as flags
		ELSE:then
			copy all the rest as args
*/
char *flags_token(t_cmd **cmd, char *prompt)
{
	int i;
	char *new_prompt;

	printf("\n->Entering flags_token\n");
	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);

		i = 0;
		// if redirections return here
		if (prompt[i] == '-')
			prompt += copy_flag(cmd, i + 1, prompt);
		else if (isquo te(prompt[i]) && prompt[i + 1] == '-')
			prompt += copy_flag(cmd, i + 2, prompt);
		else
		{
			new_prompt = args_token(cmd, i, prompt);
			if (!new_prompt)
				break;
			prompt = new_prompt;
		}
	}
	print_cmd_list(*(cmd));
	return (prompt);
}

/*
	example : ls -Flag1 -Flag2 arg1 arg2 -Flag3 > file1 file2 file3  | cat Grep "test"
		| sort | wc -l

	take the segments of commands splitted by pipes
	ex:segment[i] -> ls -Flag1 -Flag2 arg1 arg2 -Flag3 > file1 file2 file3
		-trim spaces
		-skip the prompt to the first space
		-calculate how many words skipped
			ls"test" = 8 chars
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
	printf("sturct list created & updated successfuly");
	print_cmd_list(*(cmd));
	printf("leaving<- command_token\n");
	return (prompt + len);
}

void tokenization(t_cmd **cmd, char *prompt)
{
	prompt = command_token(cmd, prompt);
	printf("\nReturned prompt=%s$len=%d\n", prompt, ft_strlen(prompt));
	if (*prompt != '\0')
		flags_token(cmd, prompt);
}