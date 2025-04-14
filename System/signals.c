/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:49:04 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/14 21:41:14 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_env **env, char *errmessage, int error_code, int fork)
{
	printf("%s\n", errmessage);
	(*env)->exit_status = 1;
	if (fork)
		exit(error_code);
	(*env)->exit_code = error_code;
}

void	handle_eof(t_env **env)
{
	printf("\nExiting minishell...\n");
	rl_clear_history();
	exit((*env)->exit_code);
}

void	handle_sigint(__attribute__((unused)) int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 130;
}

void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	restoresignal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ignoresignals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
