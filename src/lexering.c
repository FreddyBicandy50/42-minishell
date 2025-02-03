/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/03 21:04:37 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *rediretions_token(t_cmd **cmd, char *prompt, int type)
{
	char *filename;
	(void)type;
	int len;

	printf("\n\t**ENTERING REDIRECTIONS TOKEN**\n");
	prompt++;
	//TODO fix this shit
	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);
		filename = skip_to_c(prompt, ' ');
		if (redirection_near_redirirection(prompt) == NULL)
			return (NULL);
		len = filename - prompt;
		if (len <= 0)
			printf("error no filename detected");
		filename = dequotencpy(0, len, prompt);
		printf("filename=%s", filename);
		// add to s_redir;
		prompt += len;
		if (*prompt != '\0')
			prompt = skip_spaces(prompt);
		if (*prompt != '\0')
			prompt = flags_token(cmd, prompt);
		if (*prompt == '\0')
			break;
		printf("REST prompt=%s\n", prompt);
		prompt++;
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
	int type;

	prompt = command_token(&cmd, prompt);
	printf("\nRemaining Tokens=%s$ | len=%d\n", prompt, ft_strlen(prompt));
	if (*prompt != '\0')
		prompt = flags_token(&cmd, prompt);
	type = redirections(*prompt, *(prompt + 1));
	if (type < 0)
		printf("error unmatched redirections at%c`", *prompt);
	else if (type > 0)
	{
		prompt = rediretions_token(&cmd, prompt, type);
		if (!prompt)
			return (NULL);
	}
	return (cmd);
}
