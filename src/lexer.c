/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/08 23:05:41 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_next_command(char *prompt)
{
    int i;

    if (!prompt)
        return (NULL);
    i = 0;
    while (prompt[i] != '\0')
    {
        printf("%c", prompt[i]);
        i++;
    }
    printf("\n");
    return prompt;
}

void lexering(t_data *data)
{
    // 1.Loop over the input line(character by character)
    //     Start at the first character and loop until you reach the end of the input string(\0)
    //     Skip leading spaces or
    //     tabs to avoid empty tokens .
    //  2. Identify Command Tokens
    //     As you encounter a non -
    //     space character,
    //     start identifying it as part of a command or an argument.Example : bash echo hello > test
    //     Start at e,
    //     continue until you hit a space.You've now identified the command echo.
    //  3. Handle Flags / Options(e.g., -la) Once you've captured the command, look for flags/options: A flag is typically a string starting with a - , e.g., -la.Treat it as a special case and store it as a separate token.Implementation:
        // After capturing a command, check if the next character after the space is -.
        // Capture the flag as part of the argument list for the command.
        // Edge Case: There might be multiple flags, so handle -a -b -c as separate tokens or -abc as a combined token.
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
    get_next_command(skip_spaces(data->input));
}