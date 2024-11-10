/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/10 14:37:10 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

t_cmd	*lexer(char *input)
{
	int		i;
	char	**segments;
	t_cmd	*cmd;

	if (!input || *input == '\0')
		return (NULL);
	cmd = NULL;
	segments = NULL;
	segments = ft_split(input, '|');
	i = -1;
	while (segments[++i] != NULL)
		get_next_command(&cmd, segments[i]);
	free_split(segments);
	return (cmd);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	char	*input;
	t_cmd	*cmd;

	(void) argc;
	(void) argv;
	(void) envp;
	prompt = "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002";
	signals();
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
			handle_eof();
		add_history(input);
		cmd = lexer(input);
		if (cmd)
			parser(cmd, envp);
		free_cmd(cmd);
	}
	return (0);
}
