/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/10 17:29:28 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

int	main(void)
{
	t_data	data;

	signals();
	while (1)
	{
		data.input = readline(PROMPT);
		if (data.input == NULL) // Detect EOF (Ctrl+D)
		handle_eof();
		// TODO
		// Ali : SIGNALS
		// Fredy : lexering & parsing
		add_history(data.input);
		lexering(&data);
	}
	return (0);
}
