/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:42:02 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/31 00:36:26 by fbicandy         ###   ########.fr       */
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

int check_quote(char c, int quote)
{
	if (quote == 0)
	{
		if (c == '"')
			return (2);
		if (c == '\'')
			return (1);
	}
	else if (quote == 1 && c == '\'')
		return (0);
	else if (quote == 2 && c == '"')
		return (0);
	return (quote);
}

int copy_quoted_flag(t_cmd **cmd, int i, char *prompt)
{
	char *flag;
	int len;

	(void)cmd;
	printf("in copy quoted_flag=%s", prompt);
	flag = skip_to_c(prompt, ' ');
	len = flag - prompt;
	flag = dequotencpy(i, len, prompt);
	printf("\ndequoted flag -> %s\n", flag);
	update_flags(cmd, flag, (*cmd)->flag);
	return (len);
}