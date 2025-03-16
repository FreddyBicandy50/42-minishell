/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:00:19 by fbicandy          #+#    #+#             */
/*   Updated: 2025/03/16 17:01:03 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

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
	@EXAMPLE "example on dequote and copy"TEST

	start = 0
	end =33
	s=@EXAMPLE

	create a variable with enough memorie address
	Track quotes and skip them
		eg: "example"
			=> " will be skipped as well the last one

	@RETURN	example on dequote and copyTEST\0
*/
char *dequotencpy(int start, int end, char *s)
{
	int i;
	int j;
	char *dest;
	char in_quote;

	i = -1;
	j = 0;
	in_quote = '\0';
	dest = malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	while (++i < (end - start) && s[start + i])
	{
		if (in_quote != '\0' && s[start + i] == in_quote)
			in_quote = '\0';
		else if (in_quote == '\0' && isquote(s[start + i]))
		{
			expansion(NULL, s);
			in_quote = s[start + i];
		}
		else
			dest[j++] = s[start + i];
	}
	dest[j] = '\0';
	return (dest);
}

/*
	@EXAMPLE -ARG1 -FLAG2 -ARG2 > Filename

	check if the command is echo everything after we specify a flag is consider args
	except for redirections

	ELSE:then
		skip to the first space
		calc len word skiped
		copy without quotes
		update list of commands arguments
*/
int copy_args(t_cmd **cmd, char *prompt)
{
	int len;
	char *argument;

	len = 0;
	if (ft_strncmp((*cmd)->command, "echo", 4) == 0)
	{
		argument = skip_spaces(prompt);
		while (*argument != '\0' && !redirections(*argument, *(argument + 1)))
			argument++;
		len = argument - prompt;
		argument = dequotencpy(0, len, prompt);
		struct_update_args(cmd, argument);
	}
	else
	{
		argument = skip_to_c(prompt, ' ');
		len = argument - prompt;
		argument = dequotencpy(0, len, prompt);
		if (*argument == '\0')
			free(argument);
		else
			struct_update_args(cmd, argument);
	}
	return (len);
}

void expansion(t_cmd **cmd, char *str)
{
	int i;
	(void)*cmd;
	(void)str;
	(void)i;

	i = 0;


}