/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_execute5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:27 by marvin            #+#    #+#             */
/*   Updated: 2025/04/10 09:48:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increment_SHLVL(t_env **env)
{
	char	*shlvl;
	int		level;

	shlvl = get_env_value(*env, "SHLVL");
	if (!shlvl)
	level = 1;
	else
		level = ft_atoi(shlvl);
	printf("\n %d\n", level);
	level++;
	shlvl = ft_itoa(level);
	set_env("SHLVL", shlvl, env);
	printf("\n %s", shlvl);
	free (shlvl);
	printf("\n %d\n", level);
}

void	decrement_SHLVL(t_env **env)
{
	char	*shlvl;
	int		level;

	printf("anna hon");
	shlvl = get_env_value(*env, "SHLVL");
	if (!shlvl)
   	 level = 1;
	else
		level = ft_atoi(shlvl);
	level--;
	shlvl = ft_itoa(level);
	set_env("SHLVL", shlvl, env);
	free (shlvl);
}
