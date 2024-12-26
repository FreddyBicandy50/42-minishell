/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:59:05 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/26 18:49:24 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "../src/minishell.h"

static size_t	ft_wordcount(char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
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
char	*skip_quoted(char *s, char c, char *word_start)
{
	char	quote_char;
	int		in_quotes;

	(void)quote_char;
	quote_char = '\0';
	in_quotes = 0;
	while (*s && (*s != c || in_quotes))
	{
		if (*s == '\\' && isquote(*s + 1))
			s++;
		else if (isquote(*s) && (s == word_start || *(s - 1) != '\\'))
		{
			in_quotes = !in_quotes;
			if (in_quotes)
				quote_char = *s;
			else
				quote_char = '\0';
		}
		s++;
	}
	return (s);
}

int	dup_err(char **tabs, int i)
{
	if (!tabs[i])
	{
		while (i > 0)
			free(tabs[--i]);
		free(tabs);
		return (1);
	}
	return (0);
}

/*
	takes the initial input => "ls -la | test"hello world | grep test
	
	count the words and intilize the tabs
		safety check on tabs and *s
	loop threw > s 
		if s !a pipe 
			mark a word begining
			if s is a quote skip all the inside
			place this string in the tabs
				check for error while duplicating
		else skip the pipe
	return these values
*/
char	**ft_command_split(char *s, char c)
{
	char	*word_start;
	char	**tabs;
	size_t	i;

	tabs = malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!s || !tabs)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_start = s;
			s = skip_quoted(s, c, word_start);
			tabs[i] = ft_strndup(word_start, s - word_start);
			if (dup_err(tabs, i))
				return (NULL);
			i++;
		}
		else
			s++;
	}
	tabs[i] = NULL;
	return (tabs);
}
