/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:13:35 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/12 22:13:41 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char *ft_strsub(const char *s, unsigned int start, size_t len)
{
	char *substr;
	size_t i;

	if (!s || start + len > strlen(s))
		return (NULL);

	// Allocate memory for the substring (including null-terminator)
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);

	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i]; // Copy characters from the original string
		i++;
	}
	substr[i] = '\0'; // Null-terminate the new string

	return (substr);
}
