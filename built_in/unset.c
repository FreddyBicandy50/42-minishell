/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:06 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/31 13:26:39 by amokdad          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../src/minishell.h"

void	my_unset(t_cmd **cmd, char **envp)
{
	int		i;
	size_t	len;

	len = ft_strlen((*cmd)->arg[0]);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], (*cmd)->arg[0], len) == 0 && envp[i][len] == '=')
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
