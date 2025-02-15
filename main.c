/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/15 13:41:18 by fbicandy         ###   ########.fr       */
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
t_cmd *parser(char *input)
{
	t_cmd *cmd;
	char **segments;
	int i;

	printf("\n**ENTERING parser(char *%s)**\n", input);
	cmd = NULL;
	segments = NULL;
	segments = ft_shell_split(input, '|');
	if (segments == NULL)
		return (NULL);
	i = -1;
	while (segments[++i] != NULL)
	{
		printf("treating segments[%d]=%s\n", i, segments[i]);
		cmd = tokenization(cmd, segments[i]);
		if (!cmd)
			return (NULL);
	}
	cmd = struct_get_first(cmd);
	free_split(segments);
	return (cmd);
}

t_cmd *lexical_analysis(char *input)
{
	t_cmd *cmd;

	printf("\n**ENTERING lexcial_analysis(char *%s) in main.c**\n", input);
	printf("\tchecking if input is null or \\0...\n");
	if (!input || *input == '\0')
	{
		printf("\tyes leaving...\n");
		return (NULL);
	}
	cmd = NULL;
	printf("\tchecking if input starts with |...\n");
	if (input[0] == '|')
	{
		printf("\tyes leaving...\n");
		printf("minishell:error unexpected token near:%c\n", input[0]);
		return (NULL);
	}
	printf("\tinput is not null or | continuing...\n\n");
	cmd = parser(input);
	printf("**LEAVING LEXICAL_ANALYSIS**\n\n");
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
		printf("\n**ENTERING main in main.c**\n");
		input = readline(prompt);
		if (input == NULL)
			handle_eof();
		add_history(input);
		cmd = lexical_analysis(skip_spaces(input));
		free(input);
		if (cmd)
		{
			printf("\n\n");
			struct_print_list(cmd);
			executing(&cmd, envp);
			struct_free_cmd(cmd);
			printf("\tfreeing input...\n");
		}
	}
	return (0);
}
