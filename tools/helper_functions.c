/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:42:02 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/25 14:07:21 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void ft_error(t_cmd **cmd, char *message, char *str)
{
	if (str)
		printf("%s%s\n", message, str);
	else
		printf("%s\n", message);
	struct_free_cmd(*cmd);
}

void update_redirections(t_cmd **cmd, t_redir *new_redirection)
{
	t_redir *temp;

	if ((*cmd)->redirections == NULL)
		(*cmd)->redirections = new_redirection;
	else
	{
		temp = (*cmd)->redirections;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_redirection;
	}
	return;
}

int redirection_param(t_cmd **cmd, char *prompt, int type)
{
	char *filename;
	int len;
	t_redir *new_redirection;

	filename = skip_to_c(prompt, ' ');
	len = filename - prompt;
	printf("len is =%d\n", len);
	if (len <= 0)
	{
		printf("./minishell: error expected filename near %c\n",*(prompt + 1));
		return (-1);
	}
	filename = dequotencpy(0, len, prompt);
	new_redirection = (t_redir *)malloc(sizeof(t_redir));
	new_redirection->filename = filename;
	printf("filename=%s\n", filename);
	new_redirection->type = type;
	new_redirection->next = NULL;
	update_redirections(cmd, new_redirection);
	printf("LEN WILL BE %d\n\n", len);
	return (len);
}

/*
	@EXAMPLE => "helo World this is a skip to c function"Code testing

	IF C IS ' ' (AKA space)
	@RETURN "helo World this is a skip to c function"Code
*/
char *skip_to_c(char *s, char c)
{
	while (*s != '\0' && *s != c)
	{
		if (c != '|' && redirections(*s, *(s + 1)) != 0)
			break;
		if (isquote(*s))
			s = skip_inside(*s, s + 1);
		if (s == NULL)
			return (NULL);
		s++;
	}
	return (s);
}

/*
	@EXAMPLE "-FLAG1"test  -ARG1 -ARG2 -FLAG2

	Skip s to find space taking quotes into considerations
		-calculate how many chars skipped
			"-FLAG1"test = 12 chars
		-dequote the result and copy it
	send new flag to the @upate_flags functions to concat new flags tokens

	@RETURN 12 chars(how many letter we read from
	prompt to be able to skip them with prompt+=len)
*/
int copy_flag(t_cmd **cmd, int i, char *prompt)
{
	char *flag;
	int len;

	flag = skip_to_c(prompt, ' ');
	len = flag - prompt;
	flag = dequotencpy(i, len, prompt);
	struct_update_flags(cmd, flag, (*cmd)->flag);
	return (len);
}
