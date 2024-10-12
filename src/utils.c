/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:42:02 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/12 16:18:51 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str)
{
	if (!str || *str == '\0' || *str == '\n')
		return (str);
	while (!(*str >= 33 && *str <= 126) && *str != '\0')
		str++;
	return (str);
}

int	printable(char c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

int	prd(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
