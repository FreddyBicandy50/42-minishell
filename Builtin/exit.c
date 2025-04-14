/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:13 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/14 23:00:27 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_t(t_cmd **cmd, t_env **env, int tmp)
{
	struct_free_cmd(*cmd);
	free_envp(*env);
	printf("\n\nexit minishell ... \n\n");
	exit(tmp);
}

void	exit_minishell(t_cmd **cmd, t_env **env)
{
	int	tmp;
	int	i;

	tmp = 0;
	i = 0;
	if ((*cmd)->arg_number >= 2)
		printf("minishell: exit: too many arguments");
	if ((*cmd)->arg_number == 1)
	{
		while ((*cmd)->arg[0][i])
		{
			if (((*cmd)->arg[0][i] >= '0' && (*cmd)->arg[0][i] >= '9'))
			{
				tmp = 2;
				printf("minishell: exit: numeric argument required");
				break ;
			}
			i++;
			tmp = ft_atoi((*cmd)->arg[0]);
		}
		exit_t(cmd, env, tmp);
	}
	else
		exit_t(cmd, env, (*env)->exit_code);
}
