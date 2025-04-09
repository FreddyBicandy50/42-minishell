/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:09 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/09 19:22:58 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_cmd(t_env **env)
{
	t_env	*current;

	current = *env;
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
