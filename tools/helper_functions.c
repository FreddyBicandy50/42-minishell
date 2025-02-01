/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:42:02 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/01 23:09:39 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_error(t_cmd **cmd, char *message, char *str)
{
	if (str)
		printf("%s%s\n", message, str);
	else
		printf("%s\n", message);
	struct_free_cmd(*cmd);
	exit(EXIT_FAILURE);
}

/*
	@EXAMPLE => "helo World this is a skip to c function"Code testing

	IF C IS ' ' (AKA space)
	@RETURN "helo World this is a skip to c function"Code
*/
char	*skip_to_c(char *s, char c)
{
	while (*s != '\0' && *s != c)
	{
		if (c != '|' && redirections(*s, *(s + 1)) > 0)
			break;
		if (isquote(*s))
			s = skip_inside(*s, s + 1);
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
int	copy_flag(t_cmd **cmd, int i, char *prompt)
{
	char	*flag;
	int		len;

	flag = skip_to_c(prompt, ' ');
	len = flag - prompt;
	flag = dequotencpy(i, len, prompt);
	printf("flag token extracted =%s\n", flag);
	
	struct_update_flags(cmd, flag, (*cmd)->flag);
	printf("sturct list created & updated successfuly");
	
	printf("\n\t**LEAVING FLAGS TOKEN**\n");
	return (len);
}

// void	append_redirection(t_cmd **cmd, int type, char *filename)
// {
// 	t_redir	*new_redir;
// 	t_redir	*temp;

// 	new_redir = malloc(sizeof(t_redir));
// 	if (!new_redir)
// 		ft_error(cmd, "malloc failed", NULL);
// 	new_redir->type = type;
// 	new_redir->filename = filename;
// 	new_redir->next = NULL;
// 	if (!(*cmd)->redirections)
// 		(*cmd)->redirections = new_redir;
// 	else
// 	{
// 		temp = (*cmd)->redirections;
// 		while (temp->next)
// 			temp = temp->next;
// 		temp->next = new_redir;
// 	}
// }