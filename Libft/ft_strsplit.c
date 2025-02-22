/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:40:15 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/20 21:28:53 by fbicandy         ###   ########.fr       */
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
	ex: ls "HELLO |WORLD" | grep "test" | sort
	@RETURN number of commands=4
*/
int ft_split_counts(char *s, char c)
{
	size_t split_counts;

	split_counts = 0;
	s = skip_spaces(s);
	while (*s)
	{
		if (*s != c)
		{
			s = skip_to_c(s, c);
			if (!s)
				return (-1);
			split_counts++;
		}
		else
			s++;
	}
	return (split_counts);
}

/*
	ex:input => "ls -la | test" hello world | grep test

	malloc the tab //make a custome word count for more effieciency
	the usual ft_split but instead of looping threw the string here is the trick:
		we skip immidiatly to c while not taking into consideration anything
			-inside quotes
		and then we copy whetever we got

	example:
		str="ls -la | test" hello world | grep test
			skip to c = "ls -la | test" hello world
			copy this and repeat
		str=grep test
			skip to c= grep test //even if | is not found
			copy this ...
	find the manuals for skip to c for more details
*/
char **ft_shell_split(char *s, char c)
{
	char *word_start;
	char **tabs;
	int split_counts;
	size_t i;

	split_counts = ft_split_counts(s, c);
	printf("*Split_counts=%d\n\n", split_counts);
	if (split_counts <= 0)
		return (NULL);
	tabs = malloc((split_counts + 1) * sizeof(char *));
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_start = s;
			s = skip_to_c(s, c);
			tabs[i] = ft_strndup(word_start, s - word_start);
			printf("*Command_row[%ld]=%s\n", i, tabs[i]);
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
