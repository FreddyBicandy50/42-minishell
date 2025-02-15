/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:42:02 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/11 11:33:34 by fbicandy         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
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
		printf("./minishell error: no `filename` or `LIMITER` detected near %c\n", *prompt);
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
	printf("**ENTERING skip_to_c(char *%s,char %c)**\n", s, c);
	while (*s != '\0' && *s != c)
	{
		printf("\tchecking if i spot a redirection but c is not |...\n");
		if (c != '|' && redirections(*s, *(s + 1)) > 0)
		{
			printf("\tyes breaking....");
			break;
		}
		printf("\tchecking if *s is a quote to skip whatever inside\n");
		if (isquote(*s))
		{
			printf("\tyes sir skiping inside\n");
			s = skip_inside(*s, s + 1);
		}
		if (s == NULL)
		{
			printf("minishell:error near `\"\' unmatched quotes\n");
			return (NULL);
		}
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
	printf("flag token extracted =%s\n", flag);
	struct_update_flags(cmd, flag, (*cmd)->flag);
	printf("sturct list created & updated successfuly");
	printf("\n\t**LEAVING FLAGS TOKEN**\n");
	return (len);
}
