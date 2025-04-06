/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:12:46 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/06 15:18:59 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	save_original_fds(int *original_stdin, int *original_stdout)
{
	*original_stdin = dup(STDIN_FILENO);
	*original_stdout = dup(STDOUT_FILENO);
	if (*original_stdin == -1 || *original_stdout == -1)
	{
		perror("Error saving original file descriptors");
		return (-1);
	}
	return (0);
}

void	restore_original_fds(int original_stdin, int original_stdout)
{
	if (dup2(original_stdin, STDIN_FILENO) == -1)
		perror("Error restoring STDIN");
	if (dup2(original_stdout, STDOUT_FILENO) == -1)
		perror("Error restoring STDOUT");
	close(original_stdin);
	close(original_stdout);
}