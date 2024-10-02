/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2024/09/27 15:25:22 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"



int	main()
{
	char	*input;

	input = readline("MINISHELL>>: ");
	while (input != NULL)
	{
		//TODO Ali : SIGNALS
		lexering(input);
		if (strlen(input) > 0)
		{
			add_history(input);
		}
		free(input);
		input = readline("MINISHELL>>: ");
	}
	return (0);
}
