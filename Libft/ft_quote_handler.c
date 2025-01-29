/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:50:37 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/29 20:34:48 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

// TODO::dequote

/*
	example "ls -la | grep test"test hello world | grep test

	skips everything inside the quotations
	@RETURN test hello world | grep test
*/
char *skip_inside(char quote, char *s)
{
	while (*s != '\0' && *s != quote)
		s++;
	if (*s == '\0')
		return (NULL);
	return (s);
}

/*
	example Test"helo World this is a skip to c function"Code testing
	if C is space
	@RETURN Test"helo World this is a skip to c function"Code
*/
char *skip_to_c(char *s, char c)
{
	while (*s != '\0' && *s != c)
	{
		if (isquote(*s))
			s = skip_inside(*s, s + 1);
		if (s == NULL)
		{
			printf("minishell:error near `\"\' unmatched quotes\n");
			return (NULL);
		}
		s++;
	}
	return (s);
}

char *dequotencpy(int start, int end, char *s)
{
	int i, j;
	char *dest;
	char in_quote;

	i = 0;
	j = 0;
	in_quote = '\0';
	dest = malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return NULL;
	while (i < (end - start) && s[start + i])
	{
		if (in_quote != '\0' && s[start + i] == in_quote)
			in_quote = '\0';
		else if (in_quote == '\0' && isquote(s[start + i]))
			in_quote = s[start + i];
		else
			dest[j++] = s[start + i];
		i++;
	}
	dest[j] = '\0';
	return dest;
}
