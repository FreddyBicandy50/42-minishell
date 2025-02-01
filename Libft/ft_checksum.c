/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checksum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:52:13 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/01 12:57:52 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int isquote(char c)
{
	return (c == '`' || c == '\'' || c == '\"');
}

// int redirections(char c1, char c2)
// {
// 	if (c1=='>')
// 	{

// 	}
// }

char *isprintable_quote(char c)
{
	return (c >= 32 && c <= 126);
}