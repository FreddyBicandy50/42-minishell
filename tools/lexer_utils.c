/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:00:19 by fbicandy          #+#    #+#             */
/*   Updated: 2024/10/16 14:25:24 by fbicandy         ###   ########.fr       */
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
	int		j;

	while (printable(prompt[i]) && (prompt[i] != '\0' && prompt[i] != ' '))
		if (pipe_redirections(&prompt[i], NULL) > 0)
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
	j = -1;
	while ((*cmd)->flag[++j] != '\0')
	{
		if ((*cmd)->flag[j] == 32)
			(*cmd)->flag[j] = (*cmd)->flag[j + 1];
	}
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

void	handle_pipe_redirection(t_cmd **cmd, char *prompt)
{
	int	i;

	i = 0;
	if (prompt[i] == '>' && prompt[i + 1] == '>')
	{
		(*cmd)->redir_append = 1;
		i += 2;
	}
	else if (prompt[i++] == '>')
		(*cmd)->redir_out = 1;
	else if (prompt[i] == '<' && prompt[i + 1] == '<')
	{
		(*cmd)->redir_heredoc = 1;
		i += 2;
	}
	else if (prompt[i++] == '<')
		(*cmd)->redir_in = 1;
	else if (prompt[i++] == '|')
		(*cmd)->pipe = 1;
	prompt += i;
	prompt = skip_spaces(prompt);
	if ((*cmd)->pipe)
		return ;
	else
		get_next_str(cmd, prompt);
}

void append_data_node(t_data **lst, t_data *new)
{
	t_data *temp;

	if (!new || !lst)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
