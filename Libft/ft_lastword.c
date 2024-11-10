/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:42:31 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/10 11:05:21 by fredybicand      ###   ########.fr       */
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
    int j;
    int i;

    i = 0;
    j = -1;
    while (prompt[i] && prompt[i] != '<' && prompt[i] != '>')
    {
        if ((prompt[i] >= 33 && prompt[i] <= 126) &&
            (ft_isspace(prompt[i + 1]) || prompt[i + 1] == '<' || prompt[i + 1] == '>' || prompt[i + 1] == '\0'))
            j = i;
        i++;
    }
    if (j == -1)
        return (NULL);
    int start = j;
    while (start > 0 && prompt[start - 1] >= 33 && prompt[start - 1] <= 126)
        start--;
    last_word = ft_strndup(prompt + start, j - start + 1);
    if (!last_word)
        return (NULL);
    append_redirection(cmd, type, last_word);
    return (prompt + i);
}
