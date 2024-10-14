/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:28:39 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/14 17:23:02 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"

char *ft_strncpy(int start, int len, const char *src)
{
	char *dest = malloc(sizeof(char) * (len + 1)); // Allocate space for the string
	if (!dest)
		return NULL;

	int i = 0;
	while (i < len && src[start + i])
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0'; // Null-terminate the string

	return dest;
}
