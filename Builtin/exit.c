/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:13 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/12 13:26:23 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_minishell(t_cmd **cmd, t_env **env)
{
	struct_free_cmd(*cmd);
	free_envp(*env);
	printf("\n\nexit minishell ... \n\n");
	exit (0);
}
