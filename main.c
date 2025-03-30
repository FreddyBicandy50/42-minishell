/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2025/03/30 18:54:56 by fbicandy         ###   ########.fr       */
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

t_cmd *lexical_analysis(char *input, t_env *env)
{
	t_cmd *cmd;
	t_cmd *new_cmd;
	char **segments;
	int i;
	(void)*new_cmd;
	i = -1;
	cmd = NULL;
	new_cmd = NULL;
	segments = ft_shell_split(input, '|');
	segments = expansion(env, segments);
	while (segments[++i] != NULL)
	{
		new_cmd = tokenizing(segments[i]);
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

t_cmd *parsing(char *input, t_env *env)
{
	t_cmd	*cmd;
	char *next_non_space;
	int i;

	input = skip_spaces(input);
	if (!input || *input == '\0')
		return (NULL);
	i = 0;
	while (input[i])
    {
        next_non_space = skip_spaces(input + i + 1);
        if (input[0] == '|' || (i > 0 && (input[i] == '|' && next_non_space && *next_non_space == '|')))
        {
            printf("parse error near `|'\n");
            env->exit_code = 2;
            return (NULL);
        }
        i++;
    }
	if (skip_to_c(input, '\0') == NULL)
	{
		printf("minishell:Error unmatched redirections`\n");
		return (NULL);
	}
	cmd = lexical_analysis(input, env);
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
	env = save_envp(envp);
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL)
			handle_eof();
		add_history(input);
		cmd = parsing(input, env);
		free(input);
		if (cmd)
		{
			struct_print_list(cmd);
			// executing(&cmd, envp);
			struct_free_cmd(cmd);
		}
	}
	free_envp(env);
	return (0);
}
