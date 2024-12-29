/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:50:37 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/29 23:45:31 by fbicandy         ###   ########.fr       */
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
	int i;
	char *dest;
	char in_quote;

	i = 0;
	in_quote = 0;
	dest = malloc(sizeof(char) * (end + 1));
	while (i < end && s[start])
	{
		if (in_quote && s[start] == in_quote)
			in_quote = 0;
		if (!in_quote && isquote(s[start]))
		{
			in_quote = s[start++];
		}
		if (i >= end || s[start] == '\0')
			break;
		dest[i] = s[start++];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
