/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:25:22 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/14 08:26:02 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char *res;

	res = malloc(elementCount * elementSize);
	if (!res)
		return (NULL);
	ft_bzero(res, elementCount * elementSize);
	return (res);
}