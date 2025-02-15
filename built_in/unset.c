/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:06 by amokdad           #+#    #+#             */
/*   Updated: 2025/02/06 16:37:51 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	my_unset(t_cmd **cmd, char **envp)
{
	int		i;
	size_t	len;

	len = ft_strlen((*cmd)->arg[0]);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], (*cmd)->arg[0], len) == 0 && (envp[i][len] == '=' || envp[i][len] == '\0'))
		{
			while (envp[i])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			break ;
		}
		i++;
	}
}
