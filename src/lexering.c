/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/02 15:27:19 by fbicandy         ###   ########.fr       */
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
		if ((ft_strncmp((*cmd)->command, "echo", 4) != 0 && prompt[i] == ' ' && quote_flag == 0) || (prompt[i] == '>' || prompt[i] == '<'))
			break;
		i++;
	}
	if (prompt[0] == 32 || prompt[0] == '\0')
		return (0);
	if (prompt[i] == '>' || prompt[i] == '<')
		return (get_next_redirection(cmd, prompt + i));
	command = ft_strncpy(0, i, prompt);
	append_cmd(cmd, command);
	return (i);
}

/*
	get the rest of prompt from get_next_command
	loop threw prompt
		skip all leading spaces between the first command caught by gnc
		if prompt is a -
			coppy all the after to cmd->flag as flag
		else
			they are arguments go get them (whoof whoof)
		IF YOU READ THIS TOMORROW KNOW YOUR ARE KING AND JESUS LOVES YOU
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
	skip the prompt to the first space and calculate how many words skipped

*/
char *get_next_command(t_cmd **cmd, char *prompt)
{
	char *command;
	t_cmd *new_cmd;
	size_t len;

	printf("\n\nIn get_next_command i got=%s\n", prompt);
	len = 0;
	if (prompt[0] == '\0')
		return (prompt);
	if (prompt[0] == '>')
	{
		printf("TRUE ON >");
		// prompt=get filename first
	}
	command = skip_to_c(prompt, ' ');
	len = command - prompt;
	command = dequotencpy(0, len, prompt);
	printf("\nget next command got is -> %s$\n", command);
	new_cmd = ft_cmd_lst_new(command);
	ft_append_command(cmd, new_cmd);
	if (prompt[len] != '\0')
		prompt = get_next_flag(&new_cmd, (prompt + len) + 1);
	return (prompt + len);
}
