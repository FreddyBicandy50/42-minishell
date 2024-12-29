/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:40:15 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/30 00:11:24 by fbicandy         ###   ########.fr       */
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
char **ft_command_split(char *s, char c)
{
	char *word_start;
	char **tabs;
	size_t i;
	printf("\n2.(SPLIT BY [%c] STR -> [%s])\n", c, s);
	tabs = malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_start = s;
			s = skip_to_c(s, c);
			// remove this later
			printf("\t split[%ld]=", i);
			int j = 0;
			while (j < (s - word_start))
			{
				printf("%c", word_start[j]);
				j++;
			}
			printf("\n");
			//...
			if (s == NULL)
				return (NULL);
			tabs[i] = ft_strndup(word_start, s - word_start);
			printf("\n6.(DUPLICATED [%s])\n", tabs[i]);
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
