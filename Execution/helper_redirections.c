/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:12:46 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/12 15:54:42 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	save_original_fds(int *original_stdin, int *original_stdout, t_env **env)
{
	*original_stdin = dup(STDIN_FILENO);
	*original_stdout = dup(STDOUT_FILENO);
	if (*original_stdin == -1 || *original_stdout == -1)
	{
		ft_error(env, "minishell system level error", 1, false);
		return (-1);
	}
	return (0);
}

void	restore_original_fds(int original_stdin, int original_stdout,
		t_env **env)
{
	if (dup2(original_stdin, STDIN_FILENO) == -1)
		ft_error(env, "Error restoring STDIN", 1, false);
	if (dup2(original_stdout, STDOUT_FILENO) == -1)
		ft_error(env, "Error restoring STDOUT", 1, false);
	close(original_stdin);
	close(original_stdout);
}
