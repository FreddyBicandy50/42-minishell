/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:50:37 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/28 15:17:45 by fbicandy         ###   ########.fr       */
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
	char *dest;
	int i;

	printf("\n7.(DEQUOTE AND COPY GOT [%s]", s);
	i = 0;
	dest = malloc(sizeof(char) * (end + 1));
	if (!dest)
		return (NULL);
	while (i < end && s[start + i])
	{
		if (isquote(*s))
			s = skip_inside(*s, s + 1);
		if (*s == '\0')
			break;
		s++;
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	printf("AND COPIED [%s])\n", dest);
	return (dest);
}
