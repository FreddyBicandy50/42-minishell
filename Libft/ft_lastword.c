/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:52:20 by fredybicand       #+#    #+#             */
/*   Updated: 2024/11/10 11:54:52 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char *ft_last_word(t_cmd **cmd, int type, char *prompt)
{
    char *last_word;
    int j = -1;
    int i = 0;
    int start;
    char quote_char = '\0';

    while (prompt[i] && prompt[i] != '<' && prompt[i] != '>')
    {
        if (prompt[i] == '\'' || prompt[i] == '\"')
        {
            // Handle quoted text
            quote_char = prompt[i++];
            start = i;
            while (prompt[i] && prompt[i] != quote_char)
                i++;
            if (prompt[i] == quote_char)
                i++;
            j = i - 1;
        }
        else if (!ft_isspace(prompt[i]) &&
                 (ft_isspace(prompt[i + 1]) || prompt[i + 1] == '<' || prompt[i + 1] == '>' || prompt[i + 1] == '\0'))
        {
            // Handle unquoted last word
            j = i;
            i++;
        }
        else
        {
            i++;
        }
    }

    if (j == -1)
        return (NULL);
    start = j;
    while (start > 0 && !ft_isspace(prompt[start - 1]) && prompt[start - 1] != '<' && prompt[start - 1] != '>')
        start--;

    // Copy the last word or quoted section
    last_word = ft_strndup(prompt + start, j - start + 1);
    if (!last_word)
        return (NULL);

    // Append to redirections list
    append_redirection(cmd, type, last_word);
    return (prompt + i);
}
