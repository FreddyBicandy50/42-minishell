/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:09 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/19 14:44:32 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_cmd(t_env **env)
{
	t_env	*current;

	current = *env;
	set_env("_", "/usr/bin/env", env);
	while (current)
	{
		printf("%s=", current->variable_name);
		if (current->value)
			printf("%s\n", current->value);
		else
			printf("\n");
		current = current->next;
	}
	return ;
}
