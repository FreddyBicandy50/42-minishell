/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:32:57 by fredybicand       #+#    #+#             */
/*   Updated: 2024/11/15 18:07:14 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_error(t_cmd **cmd, char *message, char *str)
{
	if (str)
		printf("%s%s\n", message, str);
	else
		printf("%s\n", message);
	free_cmd(*cmd);
	exit(EXIT_FAILURE);
}
