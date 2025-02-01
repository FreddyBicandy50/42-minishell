/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:52:13 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/01 14:57:46 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	isquote(char c)
{
	return (c == '`' || c == '\'' || c == '\"');
}

int	redirections(char c1, char c2)
{
	if (c1 == '>' && c2 == '<')
		return (-1);
	if (c1 == '<' && c2 == '>')
		return (-1);
	if (c1 == '>' && c2 == '>')
		return (4);
	if (c1 == '<' && c2 == '<')
		return (3);
	if (c1 == '>')
		return (2);
	if (c1 == '<')
		return (1);
	return (0);
}

int	isprintable(char c)
{
	return (c >= 32 && c <= 126);
}