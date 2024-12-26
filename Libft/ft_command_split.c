/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:59:05 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/26 15:44:39 by fbicandy         ###   ########.fr       */
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
