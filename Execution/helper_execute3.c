/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_execute3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:24:00 by aal-mokd          #+#    #+#             */
/*   Updated: 2025/04/10 12:27:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		if (env->variable_name && env->value)
			size++;
		env = env->next;
	}
	return (size);
}

static void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**env_to_envp(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		if (env->variable_name && env->value)
		{
			tmp = ft_strjoin(env->variable_name, "=");
			envp[i++] = ft_strjoin_free(tmp, env->value);
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

static char	**build_exec_args(t_cmd *cmd)
{
	char	**args;
	int		i;
	int		j;

	i = 1;
	j = 0;
	args = malloc(sizeof(char *) * (cmd->arg_number + 3));
	if (!args)
	{
		free(args);
		return (NULL);
	}
	args[0] = cmd->command;
	while (j < cmd->arg_number)
		args[i++] = cmd->arg[j++];
	if (cmd->flag && *cmd->flag)
		args[i++] = cmd->flag;
	args[i] = NULL;
	return (args);
}

void	execute(char *path, t_cmd **cmd, char *envp[], t_env **env)
{
	char	**args;
	char	**cenvp;

	(void)envp;
	args = build_exec_args(*cmd);
	if (!args)
		ft_error(env, "malloc failed", 1);
	cenvp = env_to_envp(*env);
	if (!cenvp)
	{
		free(args);
		ft_error(env, "env error", 1);
	}
	if	(ft_strncmp("./", (*cmd)->command, 2) == 0)
		increment_SHLVL(env);
	if (execve(path, args, cenvp) == -1)
	{
		if	(ft_strncmp("./", (*cmd)->command, 2) == 0)
			decrement_SHLVL(env);
		free_string_array(cenvp);
		free(args);
		ft_error(env, "command not found", 127);
	}
}
