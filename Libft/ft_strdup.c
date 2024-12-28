/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:26:52 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/28 14:54:59 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char *ft_strndup(const char *s, size_t n)
{
	char *dup;
	size_t len;

	len = 0;
	while (s[len] != '\0' && len < n)
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	dup = ft_strncpy(0, len, s);
	printf("\n6.(DUPLICATED [%s])\n", dup);
	return (dup);
}

char *ft_strdup_until_space(char *str)
{
	int i;
	int len;
	char *copy;

	i = 0;
	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	while (i < len)
	{
		copy[i] = str[i];
		copy[len] = '\0';
		i++;
	}
	return (copy);
}

char *ft_strdup(char *s)
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
