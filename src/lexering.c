/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/27 17:43:02 by fbicandy         ###   ########.fr       */
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
	append_cmd(cmd, command);
	return (len);
}

/*
	get the rest of prompt from get_next_command
	loop threw prompt
		skip all leading spaces between the first command caught by gnc
		if prompt is a -
			copy all the after to cmd->flag as flag
		else
			they are arguments go get them (whoof whoof)
*/

char *get_next_flag(t_cmd **cmd, char *prompt)
{
	int i;
	char *new_prompt;

	while (*prompt != '\0')
	{
		prompt = skip_spaces(prompt);
		i = 0;
		if (prompt[i] == '-')
			prompt += copy_quoted_flag(cmd, i + 1, prompt);
		else if (isquote(prompt[i]) && prompt[i + 1] == '-')
			prompt += copy_quoted_flag(cmd, i + 2, prompt);
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
	take the segments of commands splitted by pipes
	example : ls -Flag1 -Flag2 arg1 arg2 -Flag3 > file1 file2 file3  | cat Grep "test" | sort | wc -l
	GNC -> ls -Flag1 -Flag2 arg1 arg2 -Flag3 > file1 file2 file3
	skip the prompt to the first space and calculate how many words skipped
*/
char *get_next_command(t_cmd **cmd, char *prompt)
{
	printf("~GNC~ Logs:\n");
	char *command;
	t_cmd *new_cmd;
	size_t len;

	prompt = skip_spaces(prompt);
	if (prompt[0] == '\0')
		return (prompt);
	// check if first this is a redirection
	len = 0;
	command = skip_to_c(prompt, ' ');
	printf("command=%s$\n", command);
	len = command - prompt;
	printf("command lenght=%d\n", len);
	command = dequotencpy(0, len, prompt);
	printf("dequoted command=%s\n", command);

	new_cmd = ft_cmd_lst_new(command);
	ft_append_command(cmd, new_cmd);
	if (prompt[len] != '\0')
		prompt = get_next_flag(&new_cmd, (prompt + len) + 1);
	return (prompt + len);
}
