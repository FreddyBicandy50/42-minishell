/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/02 21:59:23 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"



int	main()
{
	char	*input;

	input = readline(PROMPT);
	while (input != NULL)
	{
		//TODO Ali : SIGNALS
		lexering(input);
		if (strlen(input) > 0)
		{
			add_history(input);
		}
		free(input);
		input = readline(PROMPT);
	}
	return (0);
}
