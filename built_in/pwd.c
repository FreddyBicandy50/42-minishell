/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:40:18 by amokdad           #+#    #+#             */
/*   Updated: 2024/12/29 11:24:39 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	pwd_cmd(void)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL)
		printf("%s\n", new_pwd);
	else
		printf("PWD environment variable not found.\n");
	free(new_pwd);
	return ;
}
