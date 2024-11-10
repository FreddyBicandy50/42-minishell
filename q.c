/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:50:16 by fredybicand       #+#    #+#             */
/*   Updated: 2024/11/10 11:50:17 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *extract_quoted_text(const char *str)
{
    char *result = malloc(strlen(str) + 1); // Allocate enough memory
    if (!result)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    int i = 0, j = 0;
    char quote_char = '\0';

    while (str[i] != '\0')
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            quote_char = str[i];
            i++; // Move past the opening quote

            // Collect characters inside the quoted section
            while (str[i] != '\0' && str[i] != quote_char)
            {
                result[j++] = str[i++];
            }

            if (str[i] == quote_char)
                i++; // Move past the closing quote
        }
        else
        {
            result[j++] = str[i++];
        }
    }

    result[j] = '\0'; // Null-terminate the result
    return result;
}

int main()
{
    const char *input = "test'e'\"hellow woadsa dsa as\"world";
    char *output = extract_quoted_text(input);
    printf("Extracted text: %s\n", output);
    free(output); // Don't forget to free the memory
    return 0;
}
