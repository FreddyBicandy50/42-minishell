/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:06:47 by fbicandy          #+#    #+#             */
/*   Updated: 2025/03/24 22:50:21 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*join;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)malloc(s1_len + s2_len + 1);
	if (!join || !s1 || !s2)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		join[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		join[i] = *s2;
		s2++;
		i++;
	}
	join[i] = '\0';
	return (join);
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *joined;
    
    if (!s1 || !s2)
        return (NULL);
    joined = ft_strjoin(s1, s2);
    free(s1);
    return (joined);
}
