/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:09:30 by aal-mokd          #+#    #+#             */
/*   Updated: 2024/12/29 12:10:15 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ldest;
	size_t	lsrc;
	size_t	i;
	size_t	space_left;

	i = 0;
	ldest = 0;
	lsrc = 0;
	while (dst[ldest] != '\0' && ldest < size)
		ldest++;
	while (src[lsrc] != '\0')
		lsrc++;
	space_left = 0;
	if (size > ldest)
		space_left = size - ldest - 1;
	while (src[i] != '\0' && i < space_left)
	{
		dst[ldest + i] = src[i];
		i++;
	}
	if (ldest < size)
	{
		dst[ldest + i] = '\0';
	}
	return (ldest + lsrc);
}
