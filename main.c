/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/03 17:35:19 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"



int	main()
{
	char	*input;
	int input_len;
	
	input = readline(PROMPT);
	while (input != NULL)
	{
		//TODO 
			//Ali : SIGNALS
			//Fredy : lexering & parsing
		input_len=ft_strlen(input);
		if (input_len > 0)
			add_history(input);
		lexering(input, input_len);
		free(input);
		input = readline(PROMPT);
	}
	return (0);
}
