/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:07:17 by amokdad           #+#    #+#             */
/*   Updated: 2024/11/11 22:30:22 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	echo_cmd(t_cmd **cmd)
{
	int	i;
	int	j;

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
