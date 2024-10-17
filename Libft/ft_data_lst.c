/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:38:22 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/16 14:40:36 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

t_data *create_new_data_node(const char *input)
{
    t_data *new_data;

    new_data = (t_data *)malloc(sizeof(t_data));
    if (!new_data)
        return (NULL);

    new_data->input = strndup(input, strlen(input));
    if (!new_data->input)
    {
        free(new_data);
        return (NULL);
    }

    new_data->next = NULL; // Initialize the next pointer to NULL
    return (new_data);
}
