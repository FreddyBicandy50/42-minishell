/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:06 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/25 18:08:29 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

static void	update_value(int i, char *var, char *value)
{
	size_t	new_len;

	new_len = strlen(var) + strlen(value) + 1;
	environ[i] = (char *)malloc(new_len);
	if (environ[i] == NULL)
	{
		perror("malloc");
		return ;
	}
	ft_strncpy(environ[i], var, ft_strlen(var));
	ft_strcat(environ[i], value);
}

void	set_env(char *var, char *value)
{
	int		i;
	size_t	len;

	len = strlen(var);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, len))
		{
			update_value(i, var, value);
			return ;
		}
	}
	update_value(i, var, value);
	environ[i + 1] = NULL;
}

void	my_export(t_cmd **cmd)
{
	if (!cmd || !(*cmd))
		return ;
	set_env((*cmd)->var[0], (*cmd)->var[1]);
}
