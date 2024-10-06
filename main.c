/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:51:28 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/06 19:54:28 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/minishell.h"

int main(void)
{
	t_data data;

	while (1)
	{
		data.input = readline(PROMPT);
		// TODO
		// Ali : SIGNALS
		// Fredy : lexering & parsing
		add_history(data.input);
		lexering(&data);
		free(data.input);
	}
	return (0);
}
