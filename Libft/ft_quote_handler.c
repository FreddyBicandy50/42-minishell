/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:50:37 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/02 15:31:41 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

// TODO::dequote

/*
	get the string example "ls -la | grep"test | wc -l

	loop threw (s and ( [s is not a pipe] or [is not in a quote]))
		if we spot a \ and we have quote after
			skip it
		else if (quote and (s = word_start) or (the prev char of s is not \))
			flip quote signal
			save the quote shape
*/
char *skip_inside(char quote, char *s)
{
	printf("\n3.(QUOTES SKIPED [");
	while (*s != '\0' && *s != quote)
	{
		printf("%c", *s);
		s++;
	}
	printf("])\n");
	if (*s == '\0')
		return (NULL);
	return (s);
}

/*
	get the string example "ls -la | grep"test | wc -l

	loop threw (s and ( [s is not a pipe] or [is not in a quote]))
		if we spot a \ and we have quote after
			skip it
		else if (quote and (s = word_start) or (the prev char of s is not \))
			flip quote signal
			save the quote shape
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
	printf("\n4.(SCOND COMMAND WILL BE [%s])\n", s);
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
	dest = malloc(sizeof(char) * (end - start + 1)); // Allocate enough memory
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
