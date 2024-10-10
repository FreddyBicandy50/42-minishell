/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:42:02 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/10 23:01:13 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *skip_spaces(char *str)
{
    if (!str || *str == '\0' || *str == '\n')
        return (NULL);
    while (!(*str >= 33 && *str <= 126) && *str != '\0')
        str++;

    return (str);
}

int printable(char c)
{
    if (c >= 33 && c <= 126)
        return (1);
    return (0);
}
