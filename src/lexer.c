/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/02 22:54:10 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_command(char *prompt)
{
    char *command;
    int start;
    int end;

    start = 0;
    while (prompt[start] != '\0' && (prompt[start] >= 9 && prompt[start] <= 32))
        start++;
    end= start;
    while (prompt[end] != '\0' && !(prompt[end] >= 9 && prompt[end] <= 32))
        end++;
        //implement str cpy
    command = ft_strlcpy(prompt[start], end, command);
    return (prompt);
}

void lexering(char *prompt)
{
    get_command(prompt);
    return;
}