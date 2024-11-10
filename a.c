/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:33:24 by fredybicand       #+#    #+#             */
/*   Updated: 2024/11/10 20:01:40 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

char *ft_last_word(char *prompt)
{
    int i;
    int j;
    int end;
    char quote;
    int dequote;

    dequote = 0;
    i = 0;
    j = 0;
    quote = ' ';
    printf("\nPROMPT=%s\n", prompt);
    while ((prompt[j] != '>' && prompt[j] != '<') && prompt[j] != '\0')
        j++;
    i = j - 1;
    printf("INDEX:\n  i=%d \t j=%d", i, j);
    while (!(prompt[i] >= 33 && prompt[i] <= 126) && i > 0)
        i--;
    end = i;
    printf("\nlast WORD:\n\t");
    while (i > 0)
    {
        if (prompt[i] == '\'' || prompt[i] == '\"')
        {
            quote = prompt[i];
            dequote++;
        }
        if (dequote == 2)
        {
            quote = ' ';
            dequote = 0;
        }
        if (!(prompt[i] >= 33 && prompt[i] <= 126) && quote == ' ')
            break;
        i--;
    }
    while (i <=end)
        printf("%c", prompt[i++]);
    printf("$\n");
    return (prompt + j);
}

int main()
{
    char *prompt = ">Hello asj a asdsa das kalskd;a kl;kWorld     <'my name is freddy' 'that a test'   >bicandy not fbi or candy<\"its\" okeee fff\"fbicnady\"yy ";
    // res 1= World
    // res 2= 'my name is freddy'
    // res 3= candy
    // res 4= fff\"fbicnady\"yy "

    printf("\tRESULT 1");
    prompt = ft_last_word(++prompt);
    printf("\tRESULT 2");
    prompt = ft_last_word(++prompt);

    printf("\tRESULT 3");
    prompt = ft_last_word(++prompt);
    
    printf("\tRESULT 4");
    prompt = ft_last_word(++prompt);

    return (0);
}
