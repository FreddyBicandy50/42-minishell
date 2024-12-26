/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:52:13 by fbicandy          #+#    #+#             */
/*   Updated: 2024/12/27 00:02:31 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char *isprintable_quote(char *s)
{
	if (*s == '\\' && isquote(*(s + 1)))
	{
		s++;
		s++;
	}
	return (s);
}

int isquote(char c)
{
	return (c == '`' || c == '\'' || c == '\"');
}
