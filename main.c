/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2025/03/16 18:07:02 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;
/*
 *input= ls -la "test" | grep "test"
 *Steps:
 *	if string is empty or has | at the start
 *	elif split the commands by pipes
 *	each string in the returned segment is a command
 *  start tokenization method
 */
t_cmd *lexical_analysis(char *input, t_env **env)
{
	t_cmd *cmd;
	t_cmd *new_cmd;
	char **segments;
	int i;

	i = -1;
	cmd = NULL;
	new_cmd = NULL;
	segments = ft_shell_split(input, '|');
	if (segments == NULL)
		return (NULL);
	while (segments[++i] != NULL)
	{
		new_cmd = parsing(segments[i],env);
		if (!new_cmd)
		{
			struct_free_cmd(cmd);
			cmd = NULL;
			break;
		}
		else
			struct_addback_list(&cmd, new_cmd);
	}
	free_split(segments);
	return (cmd);
}

t_cmd *tokenization(char *input, t_env **env, char **envp)
{
	t_cmd *cmd;

	*env = save_envp(envp);
	if (*env == NULL)
		return NULL;
	input = skip_spaces(input);
	if (!input || *input == '\0')
		return (NULL);
	cmd = NULL;
	if (input[0] == '|')
	{
		printf("parse error near `|'\n");
		(*env)->exit_code = 2;
		return (NULL);
	}
	if (skip_to_c(input, '\0') == NULL)
	{
		printf("minishell:Error unmatched redirections`\n");
		return (NULL);
	}
	cmd = lexical_analysis(input,env);
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
	char *input;
	t_cmd *cmd;
	t_env *env;

	signals();
	(void)argv;
	(void)argc;
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL)
			handle_eof();
		add_history(input);
		cmd = tokenization(input, &env, envp);
		free(input);
		if (cmd)
		{
			// expansion(&cmd,envp);
			struct_print_list(cmd);
			// executing(&cmd, envp);
			struct_free_cmd(cmd);
		}
	}
	return (0);
}
