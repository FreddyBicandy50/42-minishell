/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/16 19:29:23 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *input= ls -la "test" | grep "test"
 *Steps:
 *	if string is empty or has | at the start
 *	elif split the commands by pipes
 *	each string in the returned segment is a command
 *  start tokenization method
 */

int		g_signal = 0;

t_cmd	*lexical_analysis(t_env *env, char **segments)
{
	t_cmd	*cmd;
	t_cmd	*new_cmd;
	int		i;

	i = -1;
	cmd = NULL;
	new_cmd = NULL;
	segments = expansion(env, segments);
	while (segments[++i] != NULL)
	{
		new_cmd = tokenizing(segments[i], env);
		if (!new_cmd)
		{
			struct_free_cmd(cmd);
			cmd = NULL;
			break ;
		}
		else
			struct_addback_list(&cmd, new_cmd);
	}
	free_split(segments);
	return (cmd);
}

t_cmd	*split_commands(char *input, t_env *env)
{
	t_cmd	*cmd;
	char	**segments;

	segments = ft_shell_split(input, '|', env);
	if (env->exit_status == 1 || segments == NULL)
		return (NULL);
	cmd = lexical_analysis(env, segments);
	return (cmd);
}

t_cmd	*parsing(char *input, t_env **env)
{
	t_cmd	*cmd;
	char	*n;
	int		i;

	cmd = NULL;
	input = skip_spaces(input);
	if (!input || *input == '\0')
		return (NULL);
	i = 0;
	while (input[i])
	{
		n = skip_spaces(input + (i + 1));
		if (input[0] == '|' || (i > 0 && ((*n == '|' || *n == '\0')
					&& input[i] == '|')))
			return (ft_error(env, "parse error near `|'", 2, false), NULL);
		i++;
	}
	if (skip_to_c(input, '\0', *env) == NULL)
		return (ft_error(env, "parse error unmatched quotes`", 2, false), NULL);
	if ((*env)->exit_status != 1)
		cmd = split_commands(input, *env);
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

int	main(int argc, char *argv[], char *envp[])
{
	char			*input;
	t_cmd			*cmd;
	static t_env	*env;

	signals();
	(void)argv;
	(void)argc;
	env = save_envp(envp);
	increment_shlvl(&env);
	while (1)
	{
		env->exit_status = 0;
		input = readline(PPOPROMPT);
		if (input == NULL)
			handle_eof(&env);
		if (g_signal == 130)
			env->exit_code = g_signal;
		g_signal = 0;
		add_history(input);
		cmd = parsing(input, &env);
		free(input);
		if (cmd && (env->exit_status != 1 && g_signal != 130))
			executing(&cmd, &env);
		struct_free_cmd(cmd);
	}
	return (free_envp(env), env->exit_code);
}
