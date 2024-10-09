/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:49:04 by amokdad           #+#    #+#             */
/*   Updated: 2024/10/09 10:46:41 by amokdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if ^d exit minishell
void	handle_eof(void)
{
	printf("\nExiting minishell...\n");
	rl_clear_history();
	exit(0);
}

//if ^c stop prompt && \n
void	handle_sigint(__attribute__((unused)) int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// // Handle SIGQUIT (Ctrl+\)
// void	handle_sigquit(__attribute__((unused)) int sig)
// {
// 	signal(SIGQUIT, SIG_IGN);
// 	//do nothing
// }

void	signals(void)
{
	// Handle (Ctrl+c)
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	// Handle (Ctrl+\) //do nothing
}