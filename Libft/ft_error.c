/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:32:57 by fredybicand       #+#    #+#             */
/*   Updated: 2024/11/10 13:44:48 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	ft_error(t_cmd **cmd, char *message, char *str)
{
	printf("%s %s", message, str);
	free_cmd(*cmd);
	exit(-1);
}
