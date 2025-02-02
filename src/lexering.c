/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/02 20:52:01 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *rediretions_token(t_cmd **cmd, char *prompt)
{
	(void)*cmd;
	(void)*prompt;
	printf("prompt got=%s", prompt);

	exit(0);

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

	printf("\n\t***ENTERING ARGS TOKEN***");
	n = copy_args(cmd, prompt);
	if (n > 0)
		prompt += n;
	else
	{
		if (prompt[i] == '\0')
			return (NULL);
		prompt++;
	}
	printf("\n\t***LEAVING ARGS TOKEN***\n");
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

	printf("\n\t**ENTERING FLAGS TOKEN**\n");
	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);
		i = 0;
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
	t_cmd *new_cmd;
	size_t len;

	printf("\n\t***ENTERING COMMAND TOKEN***\n");
	prompt = skip_spaces(prompt);
	if (prompt[0] == '\0')
		return (prompt);
	// check if first this is a redirection

	len = 0;
	command = skip_to_c(prompt, ' ');
	len = command - prompt;
	command = dequotencpy(0, len, prompt);

	printf("command token extracted =%s\n", command);
	new_cmd = struct_create_list(command, *cmd);
	*cmd = struct_addback_list(cmd, new_cmd);
	printf("sturct list created & updated successfuly");
	printf("\n\t***LEAVING COMMAND TOKEN***\n");
	return (prompt + len);
}

t_cmd *tokenization(t_cmd *cmd, char *prompt)
{
	prompt = command_token(&cmd, prompt);
	printf("\nRemaining Tokens=%s$ | len=%d\n", prompt, ft_strlen(prompt));
	if (*prompt != '\0')
		prompt = flags_token(&cmd, prompt);
	if (redirections(*prompt, *(prompt + 1) < 0))
		printf("unmatched redirections at %c`", *prompt);
	else
	{
		rediretions_token(&cmd, prompt);
		printf("redirections caught true prompt=%s\n", prompt);
	}
	return (cmd);
}
