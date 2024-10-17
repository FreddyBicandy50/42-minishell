/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:32:30 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/16 14:32:50 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t len;

    len = strnlen(s, n);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    strncpy(dup, s, len);
    dup[len] = '\0'; // Ensure null-termination
    return (dup);
}
