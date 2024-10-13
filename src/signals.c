/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:49:04 by amokdad           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/11 10:25:07 by amokdad          ###   ########.fr       */
=======
/*   Updated: 2024/10/12 16:10:46 by fbicandy         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_eof(void)
{
	printf("\nExiting minishell...\n");
	rl_clear_history();
	exit(0);
}

void	handle_sigint(__attribute__((unused)) int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

<<<<<<< HEAD
// Handle (Ctrl+c)
// Handle (Ctrl+\) //do nothing
=======
void	handle_sigquit(__attribute__((unused)) int sig)
{
	signal(SIGQUIT, SIG_IGN);
}

>>>>>>> refs/remotes/origin/main
void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
