/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2025/03/30 18:31:04 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *rediretions_token(t_cmd **cmd, char *prompt)
{
	int len;
	int type;

	while (*prompt != '\0')
	{
		type = redirections(*prompt, *(prompt + 1));
		if (type < 0)
		{
			printf("./minishell:error unmatched redirections near %c\n", *(prompt + 1));
			return (NULL);
		}
		if (type == 4 || type == 3)
			prompt += 2;
		else
			prompt++;
		prompt = skip_spaces(prompt);
		len = redirection_param(cmd, prompt, type);
		if (len == -1 || *prompt == '\0')
			return (NULL);
		prompt += len;
		if (*prompt != '\0')
			prompt = flags_token(cmd, prompt);
	}
	return (prompt);
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

	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);
		i = 0;
		if (*prompt == '\0')
			break;
		if (redirections(*prompt, *(prompt + 1)))
			break;
		if (prompt[i] == '-')
			prompt += copy_flag(cmd, i + 1, prompt);
		else if (isquote(prompt[i]) && prompt[i + 1] == '-')
			prompt += copy_flag(cmd, i + 2, prompt);
		else
		{
			new_prompt = args_token(cmd, i, prompt);
			if (!new_prompt)
				break;
			prompt = new_prompt;
		}
	}
	return (prompt);
}

/*
	@EXAMPLE : ls -Flag1 -Flag2 arg1 arg2 -Flag3 > file1 file2 file3
	take the segments of commands splitted by pipes
	ex:segment[i] -> ls -Flag1 -Flag2 arg1 arg2 -Flag3 > file1 file2 file3
		-trim spaces
		-skip the prompt to the first space
		-calculate how many words skipped
			ls"test" = 8 chars
		-dequote the result and copy it
	@RETURN  -Flag1 -Flag2 arg1 arg2 -Flag3 > file1 file2 file3
*/
char *command_token(t_cmd **cmd, char *prompt)
{
	char *command;
	size_t len;

	len = 0;
	prompt = skip_spaces(prompt);
	if (prompt[0] == '\0')
		return (prompt);
	command = skip_to_c(prompt, ' ');
	len = command - prompt;
	command = dequotencpy(0, len, prompt);
	*cmd = struct_create_list(command, *cmd);
	return (prompt + len);
}

t_cmd *tokenizing(char *prompt)
{
	t_cmd *new_cmd;

	new_cmd = NULL;
	prompt = command_token(&new_cmd, prompt);
	if (*prompt != '\0')
		prompt = flags_token(&new_cmd, prompt);
	if (*prompt != '\0')
	{
		prompt = rediretions_token(&new_cmd, prompt);
		if (!prompt)
		{
			struct_free_cmd(new_cmd);
			return (NULL);
		}
	}
	return (new_cmd);
}
