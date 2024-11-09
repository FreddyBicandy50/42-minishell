/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:26:52 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/09 10:01:28 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char *ft_strdup_until_space(const char *str)
{
	int		len;
	char	*copy;

	len= 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++; 
	copy = (char *)malloc(len + 1);
	if (!copy)
		return NULL;
	for (int i = 0; i < len; i++)
		copy[i] = str[i];
	copy[len] = '\0'; 
	return copy;
}

char *ft_strdup(const char *s)
{
	size_t len;
	size_t i;
	char *dup;

	if (s == NULL)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	dup = (char *)malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
