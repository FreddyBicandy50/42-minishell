/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/20 16:21:25 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	char	*input;
	t_cmd	*cmd;

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
		cmd = lexer(input);
		if (cmd)
			parser(cmd, envp);
		free_cmd(cmd);
	}
	return (0);
}

//TODO
	//fredy lexering 
	//Ali command exec 