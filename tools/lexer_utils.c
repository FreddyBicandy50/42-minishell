/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:00:19 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/15 00:44:20 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	append_cmd(t_cmd **cmd, char *command)
{
	char	**new_arg;
	int		j;
	int		k;

	j = 0;
	k = -1;
	if (!(*cmd)->arg)
		add_first_cmd(cmd, command);
	else
	{
		while ((*cmd)->arg[j] != NULL)
			j++;
		(*cmd)->arg_number = j + 1;
		new_arg = malloc(sizeof(char *) * (j + 2));
		if (!new_arg)
			free(command);
		while (k++ < j)
			new_arg[k] = (*cmd)->arg[k];
		new_arg[j] = command;
		new_arg[j + 1] = NULL;
		free((*cmd)->arg);
		(*cmd)->arg = new_arg;
	}
}

int	update_flags(t_cmd **cmd, int i, char *prompt, char *all_flags)
{
	char	*tmp;
	char	*flag;

	while (printable(prompt[i]) && (prompt[i] != '\0' && prompt[i] != ' '))
		if (prd(prompt[i++]))
			break ;
	flag = ft_strncpy(1, i, prompt);
	if (all_flags == NULL)
		all_flags = ft_strcat("-", flag);
	else
	{
		tmp = ft_strcat(all_flags, flag);
		free(all_flags);
		all_flags = tmp;
	}
	free(flag);
	(*cmd)->flag = all_flags;
	return (i);
}

char	*get_args(t_cmd **cmd, int i, char *prompt)
{
	int	n;

	n = 0;
	n = get_next_str(cmd, prompt);
	if (n > 0)
		prompt += n;
	else
	{
		if (prompt[i] == '\0')
			return (NULL);
		prompt++;
	}
	return (prompt);
}
