/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2024/09/27 15:20:26 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"



int main()
{

    char input[1024];

    while (1)
    {
        //TODO Ali : SIGNALS
        lexering(readline(PROMPT));
    }
    return (0);
}
