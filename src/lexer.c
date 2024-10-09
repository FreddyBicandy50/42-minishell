/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/09 23:39:41 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_next_command(char *prompt)
{
    int i;
    int start;

    prompt = skip_spaces(prompt);
    i = 0;
    while (prompt[i] != '\0' && prompt[i] != '-' && (prompt[i] >= 33 && prompt[i] <= 126))
        i++;
    start = 0;
    while (start < i)
    {
        printf("%c", *prompt);
        prompt++;
        start++;
    }
    printf("\n");
    return (prompt);
}

void lexering(t_data *data)
{
    // 1.Loop over the input line(character by character)
    // Start at the first character and loop until you reach the end of the input string(\0)
    // Skip leading spaces or tabs to avoid empty tokens .
    get_next_command(data->input);

    // 4. Handle Strings and Quoted Sections
    // For handling quoted strings:
    // If you encounter a ", start capturing the string inside the quotes, treating it as a single token.
    // Continue parsing until you find the closing ".
    // Ensure you handle both single (') and double (") quotes.
    // Edge Case:
    // Handle nested quotes carefully and ignore spaces inside quotes.
    // Example: echo "hello world" should treat "hello world" as one argument.
    // Make sure to handle special cases like echo 'single quotes' "double quotes" correctly.
    // 5. Handle Redirections (>, >>, <, <<)
    // When you encounter a redirection symbol (>, >>, <, <<):
    // Capture the command and arguments up to this point.
    // Store the redirection symbol and prepare to handle the next token (which will be the file).
    // Implementation:
    // On detecting >, >>, <, or <<, save the redirection type and index.
    // The next token after the redirection symbol should be a file name or a file descriptor.
    // Edge Case:
    // Ensure that after each redirection, spaces between the redirection symbol and the file are handled.
    // 6. Handle Pipes (|)
    // When a pipe (|) is encountered:
    // Treat it as a break between two separate commands.
    // Implementation:
    // Once you hit a pipe, treat everything before it as a separate command.
    // Reset your command extraction and start from the next character after the pipe for the next command.
    // Edge Case:
    // Consecutive pipes (e.g., | |) are invalid and should be flagged.
    // 7. Recursive Parsing of Compound Commands
    // In cases where there are multiple commands separated by |, redirection symbols, etc., handle each segment individually.
    // Implementation:
    // When a |, >, < is detected, save the current parsed command.
    // Recursively continue parsing from the next point, handling each segment until the end of the input.
    // Edge Case:
    // Handle consecutive commands properly, ensuring each segment is parsed completely before moving to the next.
    // 8. Handle Termination (\0)
    // When the end of the input is reached, handle any remaining tokens.
    // Ensure that all commands, arguments, and redirections are stored properly in a structured format (like an array or list).
}