/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:06 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/09 18:21:31 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_current(t_env *current)
{
	free(current->variable_name);
	free(current->value);
	free(current);
}

void	my_unset(t_cmd **cmd, t_env **env)
{
	size_t	len;
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	if ((*cmd)->arg == NULL)
		return ;
	len = ft_strlen((*cmd)->arg[0]);
	while (current)
	{
		if (ft_strncmp(current->variable_name, (*cmd)->arg[0], len) == 0
			&& (current->variable_name[len] == '='
				|| current->variable_name[len] == '\0'))
		{
			if (ft_strncmp((*cmd)->arg[0], "_", 1) == 0)
				return ;
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free_current(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}
