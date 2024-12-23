/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:52:13 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/23 15:40:10 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int isquote(char c)
{
    return c == '\"' || c == '\"';
}

char *dequote(char *input)
{
    int quotes_count;
    int i;
    int at_index_quote;

    i = 0;
    quotes_count = 0;
    at_index_quote=-1;
    while (input[i] != '\0')
    {
        if(input[i]=='\\' && isquote(input[i+1]))
        {
            at_index_quote=i+1;
        }
        else if (isquote)
            quotes_count += 1;
        i++;
    }
    if (quotes_count % 2 == 0)
    {
        i=0;
        while(input[i]!='\0')
        {
            
        }
    }
    else 
    {
        //here dog
    }
}