/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:38:06 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/16 15:40:51 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_env **env, char *errmessage, int error_code, int fork)
{
	printf("%s\n", errmessage);
	(*env)->exit_status = 1;
	if (fork)
		exit(error_code);
	(*env)->exit_code = error_code;
}
