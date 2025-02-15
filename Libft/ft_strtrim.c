/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:48:44 by fbicandy          #+#    #+#             */
/*   Updated: 2025/02/11 01:35:19 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

char *skip_spaces(char *str)
{
	printf("**ENTERING char *skip_spaces(*%s) in Libft/ft_strtrim.c**\n", str);
	printf("\tgot:skip_space(%s)\t\n", str);
	if (!str || *str == '\0' || *str == '\n')
	{
		printf("\tnothing to skip leaving...\n");
		return (str);
	}
	while (!(*str >= 33 && *str <= 126) && *str != '\0')
		str++;
	printf("\treturned:skip_space(%s)\n", str);
	printf("**LEAVING char *skip_spaces(*str)**\n\n");
	return (str);
}
