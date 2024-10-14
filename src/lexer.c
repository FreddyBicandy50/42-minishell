/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:53:11 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/15 00:43:20 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_str(t_cmd **cmd, char *prompt)
{
	int		i;
	int		quote;
	char	*command;

	i = 0;
	quote = 0;
	command = NULL;
	while (prompt[i] != '\0')
	{
		if ((prompt[i] == '"' || prompt[i] == '\'') && quote == 0)
			quote = 1;
		else if ((prompt[i] == '"' || prompt[i] == '\'') && quote == 1)
			quote = 0;
		if (prompt[i] == 32 && quote == 0)
			break ;
		i++;
	}
	if (prompt[0] == 32 || prompt[0] == '\0')
		return (0);
	command = ft_strncpy(0, i, prompt);
	if (!command)
		return (-1);
	append_cmd(cmd, command);
	return (i);
}

char	*get_next_flag(t_cmd **cmd, char *prompt)
{
	int		i;
	char	*new_prompt;

	while (*prompt != '\0' && !prd(*prompt))
	{
		prompt = skip_spaces(prompt);
		i = 0;
		if (prompt[i] == '-')
		{
			i++;
			prompt += update_flags(cmd, i, prompt, (*cmd)->flag);
		}
		else
		{
			new_prompt = get_args(cmd, i, prompt);
			if (!new_prompt)
				break ;
			prompt = new_prompt;
		}
	}
	return (prompt);
}

char	*get_next_command(t_cmd **cmd, char *prompt)
{
	int		i;
	char	*command;

	prompt = skip_spaces(prompt);
	i = 0;
	if (prompt[i] == '\0')
		return (prompt);
	while (prompt[i] != '\0' && printable(prompt[i]))
		i++;
	command = ft_strncpy(0, i, prompt);
	if (!command)
		return (NULL);
	*cmd = ft_cmd_lst_new(command);
	if (!*cmd)
		return (NULL);
	if (!prompt[i] == '\0')
		prompt = get_next_flag(cmd, (prompt + i) + 1);
	return (prompt + i);
}

void	lexering(t_data *data)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!data->input || *data->input == '\0')
		return ;
	data->input = get_next_command(&cmd, data->input);
	if (cmd)
		print_cmd_list(cmd);
	free_cmd(cmd);
}
