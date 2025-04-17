/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:24:52 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/17 21:13:57 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_append(t_env **env, t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_error(env, "Append redirection failed", 1, false);
		return (STDOUT_FILENO);
	}
	return (fd);
}

int	handle_write(t_env **env, t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_error(env, "Output redirection failed", 1, false);
		return (STDOUT_FILENO);
	}
	return (fd);
}

int	handle_read_file(t_env **env, t_redir *redir, bool here_doc)
{
	int	fd;

	if (here_doc)
		fd = open("/tmp/heredoc_input", O_RDONLY);
	else
		fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_error(env, "Input redirection failed", 0, false);
		return (STDIN_FILENO);
	}
	return (fd);
}

t_fd	handle_redirection(t_env **env, t_cmd *cmd)
{
	t_redir	*redir;
	t_fd	f;

	f.fd_1 = STDIN_FILENO;
	f.fd_2 = STDOUT_FILENO;
	redir = cmd->redirections;
	if (redir == NULL)
		return (f);
	while (redir)
	{
		if (redir->type == 1)
			f.fd_1 = handle_read_file(env, redir, FALSE);
		else if (redir->type == 2)
			f.fd_2 = handle_write(env, redir);
		else if (redir->type == 3)
		{
			f.fd_1 = handle_read_file(env, redir, TRUE);
		}
		else if (redir->type == 4)
			f.fd_2 = handle_append(env, redir);
		redir = redir->next;
	}
	return (f);
}
