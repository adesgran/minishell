/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:41:35 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 16:13:47 by adesgran         ###   ########.fr       */
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
		if (ft_strncmp(var, env->var, ft_strlen(var)) \
				&& ft_strlen(env->var) == ft_strlen(var))
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
	if (ft_strncmp(var, env->var, ft_strlen(var)) \
			&& ft_strlen(var) == ft_strlen(env->var))
	{
		origin = env->next;
		return (free(env->var), free(env->value), free(env), origin);
	}
	while (env)
	{
		if (ft_strncmp(var, env->next->var, ft_strlen(var)) \
				&& ft_strlen(var) == ft_strlen(env->var))
		{
			temp = env->next;
			env->next = temp->next;
			return (free(temp->var), free(temp->value), free(temp), origin);
		}
		env = env->next;
	}
	return (origin);
}

void	push_back_env(t_env *env, char *str)
{
	t_env	*new;
	char	**strs;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	strs = ft_split(str, '=');
	if (!strs)
		return (free(new));
	new->next = NULL;
	while (env->next)
		env = env->next;
	new->var = strs[0];
	new->value = strs[1];
	env->next = new;
	free(strs);
}

t_env	*init_env(char **env)
{
	t_env	*res;

	if (!env || !*env)
		return (NULL);
	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->next = NULL;
	res->var = ft_strdup(*env);
	while (ft_strncmp(*env, "_=", 2) == 0)
	{
		env++;
		push_back_env(res, *env);
	}
	return (res);
}
