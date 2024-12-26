/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:50:37 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/26 23:59:23 by fbicandy         ###   ########.fr       */
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
	while (*s != '\0')
	{
		s = isprintable_quote(s);
		if (*s == '\0')
			break;
		if (*s == quote)
			return (s);
		s++;
	}
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
char *skip_quoted(char *s, char c)
{
	printf("I GOT=%s", s);
	while (*s != '\0' && *s != c)
	{
		s = isprintable_quote(s);
		if (*s == '\0')
			break;
		if (isquote(*s))
		{
			printf("\nENTERED QUOTE ON:%c$\n", *s);
			s = skip_inside(*s, s + 1);
			if (*s == '\0')
				return (s);
		}
		s++;
	}
	return (s);
}