/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:40:18 by amokdad           #+#    #+#             */
/*   Updated: 2025/03/16 18:11:45 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
