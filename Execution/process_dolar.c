/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dolar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-mokd <aal-mokd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:03:21 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/13 18:32:47 by aal-mokd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

char	*gett_env_value(char *var_name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(var_name, env->variable_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	process_dollar_strings(char **input, t_env *env)
{
	char	*result;
	char	*src;
	char	key[128];
	int		i;
	int		j;
	char	temp[2];
	char	*value;

	result = calloc(BUFFER_SIZE, sizeof(char));
	if (!result)
		return ;
	src = *input;
	i = 0;
	while (src[i])
	{
		if (src[i] == '$' && src[i + 1] && (isalpha(src[i + 1]) || src[i + 1] == '_'))
		{
			i++;
			j = 0;
			while (src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
				key[j++] = src[i++];
			key[j] = '\0';
			value = gett_env_value(key, env);
			if (value)
				ft_strcat(result, value);
			else
				return;
		}
		else
		{
			temp[0] = src[i++];
			temp[1] = '\0';
			ft_strcat(result, temp);
		}
	}
	free(*input);
	*input = result;
}
