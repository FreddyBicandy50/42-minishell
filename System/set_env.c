/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:06:11 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/03/16 23:03:07 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_envp(t_env *env)
{
	t_env *temp;

	while (env != NULL)
	{
		temp = env;
		free(env->variable_name);
		env = env->next;
		free(temp);
	}
}

t_env *save_envp(char **envp)
{
	t_env *head = NULL;
	t_env *temp = NULL;

	while (*envp)
	{
		t_env *new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return NULL;
		new_node->variable_name = ft_strdup(*envp);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			temp->next = new_node;
		temp = new_node;
		envp++;
	}
	return head;
}

static void update_value(int i, char *var, char *value, char **envp)
{
	size_t new_len;

	new_len = ft_strlen(var) + ft_strlen(value) + 1;
	envp[i] = (char *)malloc(new_len);
	if (envp[i] == NULL)
	{
		perror("malloc");
		return;
	}
	ft_strlcpy(envp[i], var, ft_strlen(var) + 1);
	ft_strcat(envp[i], value);
}

void set_env(char *var, char *value, char **envp)
{
	int i;
	size_t len;

	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
		{
			update_value(i, var, value, envp);
			return;
		}
		i++;
	}
	update_value(i, var, value, envp);
	envp[i + 1] = NULL;
}
