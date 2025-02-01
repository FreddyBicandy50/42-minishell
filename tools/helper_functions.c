/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:42:02 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/01 12:53:32 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char *skip_spaces(char *str)
{
	if (!str || *str == '\0' || *str == '\n')
		return (str);
	while (!(*str >= 33 && *str <= 126) && *str != '\0')
		str++;
	return (str);
}

int printable(char c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

int pipe_redirections(char *str, int *is_double)
{
	if (is_double != NULL)
		*is_double = 0;
	if (*str == '>' || *str == '<' || *str == '|')
	{
		if ((*str == '>' && *(str + 1) == '>') || (*str == '<' && *(str + 1) == '<'))
		{
			if (is_double != NULL)
				*is_double = 1;
			return (2);
		}
		return (1);
	}
	return (0);
}

/*
	@EXAMPLE "-FLAG1"test  -ARG1 -ARG2 -FLAG2

	Skip s to find space taking quotes into considerations
		-calculate how many chars skipped
			"-FLAG1"test = 12 chars
		-dequote the result and copy it
	send new flag to the @upate_flags functions to concat new flags tokens

	@RETURN 12 chars (how many letter we read from prompt to be able to skip them with prompt+=len)
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

	print_cmd_list(*(cmd));
	printf("leaving<- flag_token\n");

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
