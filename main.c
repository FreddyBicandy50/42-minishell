/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/29 22:48:02 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

/*
 *input= ls -la "test" | grep "test"
 *Steps:
 *	if string is empty or has | at the start
 *	elif split the commands by pipes
 *	each string in the returned segment is a command
 *  start tokenization method
 */
t_cmd *lexical_analysis(char *input)
{
	int		i;
	char	**segments;
	t_cmd	*cmd;

	printf("*****************LOGS STARTED***************\n");
	if (!input || *input == '\0')
		return (NULL);

	cmd = NULL;
	segments = NULL;
	if (input[0] == '|')
	{
		printf("minishell:error unexpected token near:%c\n", input[0]);
		return (NULL);
	}

	segments = ft_split(input, '|');
	if (segments == NULL)
		return (NULL);

	i = -1;
	while (segments[++i] != NULL)
	{
		printf("Treating Segment[%d]=%s\n", i, segments[i]);
		tokenization(&cmd, segments[i]);
	}
	free_split(segments);
	return (cmd);
}

/*
	Program Workflow

	input -> lexical analysis -> parser -> executing

	*input phase handle signals and user string
	*lexical analysis:
		-takes the whole input and degridate it to mutlitple commnads
			depending on pipes
		-each command then will be analysized to determine the:
			.command Name
			.flags
			.arguments
		-handle neccesary dequoting
	*parser phase pass all data and fetch environment to execute
*/
int main(int argc, char *argv[], char *envp[])
{
	char *prompt;
	char *input;
	t_cmd *cmd;

	(void)argc;
	(void)argv;
	(void)envp;
	prompt = "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002";
	signals();
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
			handle_eof();
		add_history(input);
		cmd = lexical_analysis(input);
		if (cmd)
		{
			parser(&cmd, envp);
			free_cmd(cmd);
		}
	}
	return (0);
}
