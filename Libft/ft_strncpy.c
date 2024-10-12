/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:28:39 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/12 16:16:15 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"

char	*ft_strncpy(int start, int end, char *src)
{
	int		i;
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (start < end)
	{
		dst[i] = src[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
