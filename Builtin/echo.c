/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:07:17 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/09 15:00:42 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_cmd(t_cmd **cmd, t_env **env)
{
	int	i;
	int	j;

	(void)env;
	if ((*cmd)->arg == NULL && (*cmd)->flag != NULL
		&& ft_strcmp((*cmd)->flag, "-n") == 0)
		return ;
	if ((*cmd)->arg == NULL)
	{
		printf("\n");
		return ;
	}
	i = 0;
	while ((*cmd)->arg[i] != NULL)
	{
		j = 0;
		while ((*cmd)->arg[i][j] != '\0')
		{
			if ((*cmd)->arg[i][j] != '"')
				printf("%c", (*cmd)->arg[i][j]);
			j++;
		}
		i++;
	}
	if ((*cmd)->flag == NULL || ft_strcmp((*cmd)->flag, "-n") != 0)
		printf("\n");
}
