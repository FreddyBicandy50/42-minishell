/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/03 17:38:23 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_parser(size_t start, char *prompt, const size_t prompt_len)
{
    char *command;
    size_t end;

    while (start < prompt_len && (prompt[start] >= 9 && prompt[start] <= 32))
        start++;
    if (start >= prompt_len)
        return NULL;
    end = start;
    while (end < prompt_len && !(prompt[end] >= 9 && prompt[end] <= 32))
        end++;
    command = ft_strncpy(start, end, prompt);
    if (command)
        printf("Parsed token: '%s'\n", command); // Display the parsed token
    return command;
}

void lexering(char *prompt, const size_t prompt_len)
{
    size_t start;
    char *command;

    start = 0;
    while (start < prompt_len)
    {
        //TODO 
            //Fix quotation parser
            //create a struct for the commands
            //store the commands in the struct according to the prirority
        command = get_parser(start, prompt, prompt_len);
        if (command == NULL)
            break;
        start += strlen(command);
        while (start < prompt_len && (prompt[start] >= 9 && prompt[start] <= 32))
            start++;
        free(command);
    }
}
