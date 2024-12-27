/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:06 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/26 13:39:14 by amokdad          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../src/minishell.h"

void my_unset(t_cmd **cmd)
{
	int i = 0;
	size_t len = strlen((*cmd)->arg[0]);

	while (environ[i])
	{
		if (strncmp(environ[i], (*cmd)->arg[0], len) == 0 && environ[i][len] == '=')
		{
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			environ[i] = NULL;
			break;
		}
		i++;
	}
}
