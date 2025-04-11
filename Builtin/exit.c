/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:13 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/10 11:47:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_minishell(t_cmd **cmd, t_env **env)
{
	// decrement_SHLVL(env);
	struct_free_cmd(*cmd);
	free_envp(*env);
	printf("\n\nexit minishell ... \n\n");
	exit (0);
}
