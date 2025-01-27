/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:40:15 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/27 18:00:17 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void free_split(char **args)
{
	int i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	if (args != NULL)
		free(args);
}

/*
	takes the initial input => "ls -la | test" hello world | grep test

	count the words and intilize the tabs [49]
		safety check on tabs and *s
	loop threw > s [51]
		if s !a pipe [53]
			mark a word begining [55]
			if s is a quote skip all the inside [56]
			place this string in the tabs [59-64]
		else skip the pipe 72
	return these values 76
*/
char **ft_split_by_c(char *s, char c)
{
	char *word_start;
	char **tabs;
	size_t i;

	tabs = malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_start = s;
			s = skip_to_c(s, c);
			if (s == NULL)
				return (NULL);
			tabs[i] = ft_strndup(word_start, s - word_start);
			i++;
		}
		else
			s++;
	}
	tabs[i] = NULL;
	return (tabs);
}

char **ft_split(char *s, char c)
{
	const char *word_start;
	char **tabs;
	size_t i;

	tabs = malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!s || !tabs)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_start = s;
			while (*s && *s != c)
				s++;
			tabs[i] = ft_strndup(word_start, s - word_start);
			if (!tabs[i])
				return (NULL);
			i++;
		}
		else
			s++;
	}
	tabs[i] = NULL;
	return (tabs);
}
