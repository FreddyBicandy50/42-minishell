/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:54:15 by fbicandy          #+#    #+#             */
/*   Updated: 2025/01/29 18:55:56 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"


// void	append_redirection(t_cmd **cmd, int type, char *filename)
// {
// 	t_redir	*new_redir;
// 	t_redir	*temp;

// 	new_redir = malloc(sizeof(t_redir));
// 	if (!new_redir)
// 		ft_error(cmd, "malloc failed", NULL);
// 	new_redir->type = type;
// 	new_redir->filename = filename;
// 	new_redir->next = NULL;
// 	if (!(*cmd)->redirections)
// 		(*cmd)->redirections = new_redir;
// 	else
// 	{
// 		temp = (*cmd)->redirections;
// 		while (temp->next)
// 			temp = temp->next;
// 		temp->next = new_redir;
// 	}
// }

