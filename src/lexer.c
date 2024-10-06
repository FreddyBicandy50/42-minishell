/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/06 21:15:32 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_exceptions(char *input)
{
    int i;

    i = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '&' || input[i] == ';')
        {
            printf("minishell:syntax error near unexpected token %c\n", input[i]);
            return (1);
        }
        else if (input[i] == '|' && input[i++] == '|')
        {
            printf("minishell:syntax error near unexpected token %c\n", input[i]);
            return (1);
        }
        i++;
    }
    return (0);
}

char *get_next_command(char *prompt)
{
    int i;

    i = 0;
    while (prompt[i] != '\0')
        printf("%c", prompt[i++]);
    printf("\n");
    return (prompt);
}

void lexering(t_data *data)
{
    if (find_exceptions(data->input))
        return;
    get_next_command(data->input);
}
