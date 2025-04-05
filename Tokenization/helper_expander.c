/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:44:06 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/03 13:06:12 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_expansion(t_expand *expander, char **segments)
{
	int	i;

	expander->section = ft_strdup(" ");
	expander->prev_section = NULL;
	i = 0;
	while (segments[i])
		i++;
	expander->expanded_segements = malloc(sizeof(char *) * (i + 1));
	return (-1);
}

char	*expand(t_env *env, char *key)
{
	char	*expanded;
	char	*rawvar;
	char	*value;
	int		i;

	if (*key != '$')
		return (NULL);
	key++;
	if (*key >= '0' && *key <= '9')
	{
		key++;
		return (ft_strdup(key));
	}
	i = 0;
	while (key[i] != '\0' && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	rawvar = ft_strndup(key, i);
	value = get_env_value(env, rawvar);
	free(rawvar);
	key += i;
	if (value == NULL)
		return (ft_strdup(key));
	expanded = ft_strjoin(value, key);
	free(value);
	return (expanded);
}

void	expansion_mechanism(t_expand *expander, t_env *env)
{
	while (expander->section)
	{
		free(expander->section);
		expander->section = ft_strdup(skip_to_c(expander->next_section, '$',
					env->expanding));
		if (!expander->section || !*expander->section)
			break ;
		expander->len_section = skip_to_c(expander->next_section, '$',
				env->expanding) - expander->next_section;
		expander->var_value = expand(env, expander->section);
		expander->prev_section = ft_strndup(expander->next_section,
				expander->len_section);
		free(expander->next_section);
		expander->next_section = ft_strjoin(expander->prev_section,
				expander->var_value);
		free(expander->prev_section);
		free(expander->var_value);
	}
}

// int	expansion_quotes(int index, char *s, char **dest, t_env *env)
// {
// 	char	quotes;
// 	char	*prev;
// 	char	*next;
// 	char	**quoted_str;

// 	quotes = s[index++];
// 	s += index;
// 	next = strdup(s);
// 	index = 0;
// 	while (next[index] != quotes)
// 		index++;
// 	quoted_str = malloc(sizeof(char *) * 2);
// 	quoted_str[0] = strndup(s, index);
// 	quoted_str[1] = NULL;
// 	quoted_str = expansion(env, quoted_str);
// 	prev = strdup(*dest);
// 	free(*dest);
// 	*dest = ft_strjoin_extra(prev, quoted_str[0], ft_strlen(next + index + 1));
// 	free_split(quoted_str);
// 	free(next);
// 	free(prev);
// 	return (index);
// }
