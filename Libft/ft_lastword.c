/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:42:31 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/09 16:49:59 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char *get_last_word(t_cmd **cmd, int type, char *prompt)
{
    char *last_word;

    last_word = NULL;
    while (*prompt && *prompt != '<' && *prompt != '>')
    {
        if (!ft_isspace(*prompt))
        {
            last_word = prompt;
            while (*prompt && !ft_isspace(*prompt) && *prompt != '<' && *prompt != '>')
                prompt++;
        }
        if (*prompt == '>' || *prompt == '<')
            break;
        else
            prompt++;
    }
    if (!last_word)
        return (NULL);
    append_redirection(cmd, type, ft_strdup_until_space(last_word));
    return prompt;
}
