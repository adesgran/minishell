/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:41:35 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/03 17:03:54 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->var);
		free(env->value);
		free(env);
		env = next;
	}
}

t_env	*get_var_env(t_env *env, char *var)
{
	while (env)
	{
		if (ft_strcmp(var, env->var) == 0)
			return (env);
		env = env->next;
	}
	return (env);
}

t_env	*remove_var_env(t_env *env, char *var)
{
	t_env	*temp;
	t_env	*origin;

	origin = env;
	if (ft_strcmp(var, env->var) == 0 && env)
	{
		origin = env->next;
		if (env->value)
			free(env->value);
		return (free(env->var), free(env), origin);
	}
	while (env->next)
	{
		if (ft_strcmp(var, env->next->var) == 0)
		{
			temp = env->next;
			env->next = temp->next;
			if (temp->value)
				free(temp->value);
			return (free(temp->var), free(temp), origin);
		}
		env = env->next;
	}
	return (origin);
}

void	push_back_env(t_env *env, char *var, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->next = NULL;
	while (env->next)
		env = env->next;
	new->var = var;
	new->value = value;
	env->next = new;
}

t_env	*init_env(char **env)
{
	t_env	*res;
	char	**strs;
	char	**new;

	if (!env || !*env)
		return (init_empty_env());
	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->next = NULL;
	strs = ft_split_first(*env, '=');
	if (!strs)
		return (free(res), NULL);
	res->var = strs[0];
	res->value = strs[1];
	free(strs);
	while (env[1])
	{
		env++;
		new = ft_split_first(*env, '=');
		push_back_env(res, new[0], new[1]);
		free(new);
	}
	return (res);
}
