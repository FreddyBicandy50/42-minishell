/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:06 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/26 18:51:04 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	my_unset(t_cmd **cmd)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen((*cmd)->arg[0]);
	while (environ[i])
	{
		if (strncmp(environ[i], (*cmd)->arg[0], len) == 0
			&& environ[i][len] == '=')
		{
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			environ[i] = NULL;
			break ;
		}
		i++;
	}
}
