/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokdad <amokdad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:06:11 by aal-mokd          #+#    #+#             */
/*   Updated: 2024/12/31 13:18:41 by amokdad          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../src/minishell.h"

static void	update_value(int i, char *var, char *value, char **envp)
{
	size_t	new_len;

	new_len = ft_strlen(var) + ft_strlen(value) + 1;
	envp[i] = (char *)malloc(new_len);
	if (envp[i] == NULL)
	{
		perror("malloc");
		return ;
	}
	ft_strlcpy(envp[i], var, sizeof(var));
	ft_stralicat(envp[i], value);
}

void	set_env(char *var, char *value, char **envp)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
		{
			update_value(i, var, value, envp);
			return ;
		}
		i++;
	}
	update_value(i, var, value, envp);
	envp[i + 1] = NULL;
}

