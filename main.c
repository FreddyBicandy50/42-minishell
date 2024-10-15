/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/15 17:19:36 by amokdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	prompt = "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002";
	signals();
	while (1)
	{
		data.input = readline(prompt);
		if (data.input == NULL)
			handle_eof();
		add_history(data.input);
		lexering(&data);
	}
	return (0);
}

//TODO
	//fredy lexering 
	//Ali command exec 