/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:43:06 by amokdad           #+#    #+#             */
/*   Updated: 2025/03/16 18:11:43 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// export function work :
// first check if '=' iclude the last word of variable
// next if yes split at '='
// finaly set_env the variable and the value
// or if not do nothing and return
void	my_export(t_cmd **cmd, char **envp)
{
	int		i;
	char	*equal_sign;
	char	**name;

	if (!cmd || !(*cmd) || !(*cmd)->arg)
		return ;
	i = 0;
	while ((*cmd)->arg[i])
	{
		equal_sign = ft_strchr((*cmd)->arg[i], '=');
		if (equal_sign != NULL)
		{
			name = ft_split((*cmd)->arg[i], '=');
			set_env(name[0], equal_sign, envp);
			free(name);
		}
		i++;
	}
	return ;
}
