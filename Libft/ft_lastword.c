/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:42:31 by fbicandy          #+#    #+#             */
/*   Updated: 2024/11/09 13:03:48 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char *get_last_word(t_cmd **cmd, char *prompt)
{
    char *last_word = NULL;

    prompt = skip_spaces(prompt);

    // Loop through prompt until we encounter a space or redirection
    while (*prompt && *prompt != '<' && *prompt != '>')
    {
        if (!ft_isspace(*prompt))
        {
            last_word = prompt; // Set the start of the last word
            // Move through the word until space or redirection is encountered
            while (*prompt && !ft_isspace(*prompt) && *prompt != '<' && *prompt != '>')
                prompt++;
        }
        else
        {
            prompt++;
        }
    }

    // If no valid word was found, return NULL
    if (!last_word)
        return (NULL);

    // Copy the last word up to the space or redirection
    (*cmd)->filename = ft_strdup_until_space(last_word);

    // Return the updated prompt position
    return prompt;
}
