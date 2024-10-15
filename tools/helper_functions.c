/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:42:02 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/15 13:43:01 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

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

int	pipe_redirections(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	check_quote(char c, int quote)
{
	if ((c == '"' || c == '\'') && quote == 0)
		return (1);
	else if ((c == '"' || c == '\'') && quote == 1)
		return (0);
	return (0);
}
