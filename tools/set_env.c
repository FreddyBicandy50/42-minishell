/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:06:11 by aal-mokd          #+#    #+#             */
/*   Updated: 2024/12/27 16:29:09 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

static void	update_value(int i, char *var, char *value)
{
	size_t	new_len;

	new_len = ft_strlen(var) + ft_strlen(value) + 1;
	environ[i] = (char *)malloc(new_len);
	if (environ[i] == NULL)
	{
		perror("malloc");
		return ;
	}
	strncpy(environ[i], var, ft_strlen(var));
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
