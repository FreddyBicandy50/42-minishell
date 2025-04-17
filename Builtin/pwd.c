/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:40:18 by amokdad           #+#    #+#             */
/*   Updated: 2025/04/17 14:10:46 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_cmd(t_env **env)
{
	char	*new_pwd;
	char	*current_pwd;

	new_pwd = getcwd(NULL, 0);
	current_pwd = get_env_value(*env, "PWD");
	if (new_pwd != NULL)
		printf("%s\n", new_pwd);
	else if (current_pwd != NULL)
		printf("%s\n", current_pwd);
	else
		printf("PWD environment variable not found.\n");
	free(new_pwd);
	free(current_pwd);
	return ;
}
