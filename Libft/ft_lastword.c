/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredybicandy <fredybicandy@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:52:20 by fredybicand       #+#    #+#             */
/*   Updated: 2024/11/11 22:22:12 by fredybicand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

void	find_last_word(int *i, int *j, int *end, char *prompt)
{
	while ((prompt[*j] != '>' && prompt[*j] != '<') && prompt[*j] != '\0')
		(*j)++;
	*i = *j - 1;
	while (!(prompt[*i] >= 33 && prompt[*i] <= 126) && *i > 0)
		(*i)--;
	*end = *i;
}

int	reset(char quote, int dequote)
{
	(void)quote;
	if (dequote == 2)
	{
		quote = ' ';
		dequote = 0;
	}
	return (dequote);
}

char	*ft_last_word(t_cmd **cmd, int type, char *prompt)
{
	int		i;
	int		j;
	int		end;
	int		dequote;
	char	quote;

	dequote = 0;
	i = 0;
	j = 0;
	quote = ' ';
	find_last_word(&i, &j, &end, prompt);
	while (i > 0)
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
		{
			quote = prompt[i];
			dequote++;
		}
		dequote = reset(quote, dequote);
		if (!printable(prompt[i]) && quote == ' ')
			break ;
		i--;
	}
	append_redirection(cmd, type, ft_strndup(prompt + i, end - i + 1));
	return (prompt + j);
}
