/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:52:20 by fredybicand       #+#    #+#             */
/*   Updated: 2024/11/10 17:33:19 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

// char *ft_last_word(t_cmd **cmd, int type, char *prompt)
// {
// 	char *last_word;
// 	int j;
// 	int i;
// 	int start;
// 	char quote_char;

// 	i = 0;
// 	j = -1;
// 	quote_char = '\0';

// 	while (prompt[i] && prompt[i] != '<' && prompt[i] != '>')
// 	{
// 		if (prompt[i] == '\'' || prompt[i] == '\"')
// 		{
// 			quote_char = prompt[i++];
// 			start = i;
// 			while (prompt[i] && prompt[i] != quote_char)
// 				i++;
// 			if (prompt[i] == quote_char)
// 				i++;
// 			j = i - 1;
// 		}
// 		// If not inside quotes, handle redirection and spaces
// 		else if (!ft_isspace(prompt[i]) && (ft_isspace(prompt[i + 1]) || prompt[i + 1] == '<' || prompt[i + 1] == '>' || prompt[i + 1] == '\0'))
// 		{
// 			j = i;
// 			i++;
// 		}
// 		else
// 			i++;
// 	}
// 	if (j == -1)
// 		return (NULL);
// 	start = j;
// 	while (start > 0 && !ft_isspace(prompt[start - 1]) && prompt[start - 1] != '<' && prompt[start - 1] != '>')
// 		start--;
// 	last_word = ft_strndup(prompt + start, j - start + 1);
// 	if (!last_word)
// 		return (NULL);
// 	append_redirection(cmd, type, last_word);
// 	return (prompt + i);
// }

