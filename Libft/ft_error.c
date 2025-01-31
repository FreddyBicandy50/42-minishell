/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:32:57 by fredybicand       #+#    #+#             */
/*   Updated: 2025/01/31 19:55:32 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_error(t_cmd **cmd, char *message, char *str)
{
	if (str)
		printf("%s%s\n", message, str);
	else
		printf("%s\n", message);
	struct_free_cmd(*cmd);
	exit(EXIT_FAILURE);
}
