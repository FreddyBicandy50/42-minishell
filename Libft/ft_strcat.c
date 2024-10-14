/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:45:43 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/15 00:52:47 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char	*ft_strcat(const char *dest, const char *src)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;
	char	*new_str;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	new_str = (char *)malloc(sizeof(char) * (dest_len + src_len + 1));
	i = 0;
	while (i < dest_len)
	{
		new_str[i] = dest[i];
		i++;
	}
	j = 0;
	while (j < src_len)
	{
		new_str[i] = src[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}
