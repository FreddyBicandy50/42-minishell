/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:44:06 by fbicandy          #+#    #+#             */
/*   Updated: 2025/04/16 16:42:26 by fbicandy         ###   ########.fr       */
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
					env));
		if (!expander->section || !*expander->section)
			break ;
		expander->len_section = skip_to_c(expander->next_section, '$', env)
			- expander->next_section;
		if (ft_strncmp(expander->section, "$?", 2) == 0)
		{
			expander->var_value = ft_itoa(env->exit_code);
			env->exit_code = 0;
		}
		else
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
