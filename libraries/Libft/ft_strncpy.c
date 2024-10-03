/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:28:39 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/03 17:29:51 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"

char *ft_strncpy(size_t start, size_t end, char *src)
{
    int     i;
    char    *dst;

    i = 0;
    if (start > end || src == NULL)
        return NULL;
    dst = (char *)malloc(sizeof(char) * (end - start) + 1);
    if (dst == NULL)
        return NULL; // Return NULL if memory allocation fails
    while (start < end)
    {
        dst[i] = src[start];
        start++;
        i++;
    }
    dst[i] = '\0';
    return (dst);
}