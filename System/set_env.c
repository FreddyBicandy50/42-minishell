/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:06:11 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/02 17:32:38 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_envp(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env;
		free(env->variable_name);
		env = env->next;
		free(temp);
	}
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->variable_name, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

t_env	*save_envp(char **envp)
{
	t_env	*head;
	t_env	*temp;
	t_env	*new_node;
	char	**var_values;

	head = NULL;
	temp = NULL;
	while (*envp)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		var_values = ft_split(*envp, '=');
		new_node->variable_name = ft_strdup(var_values[0]);
		new_node->value = ft_strdup(var_values[1]);
		free_split(var_values);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			temp->next = new_node;
		temp = new_node;
		envp++;
	}
	head->exit_status = 0;
	head->exit_code = 0;
	head->expanding = FALSE;
	head->expand_index = 0;
	return (head);
}

static void	update_value(int i, char *var, char *value, char **envp)
{
	size_t	new_len;

	new_len = ft_strlen(var) + ft_strlen(value) + 1;
	envp[i] = (char *)malloc(new_len);
	if (envp[i] == NULL)
	{
		perror("malloc");
		return ;
	}
	ft_strlcpy(envp[i], var, ft_strlen(var) + 1);
	ft_strcat(envp[i], value);
}

void	set_env(char *var, char *value, char **envp)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
		{
			update_value(i, var, value, envp);
			return ;
		}
		i++;
	}
	update_value(i, var, value, envp);
	envp[i + 1] = NULL;
}
