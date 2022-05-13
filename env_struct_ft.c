/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:41:35 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 12:26:54 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env);
		env = next;
	}
}

t_env	*get_var_env(t_env *env, char *var)
{
	char	*to_check;

	while (env)
	{
		to_check = ft_strjoin(var, "=");
		if (ft_strncmp(to_check, env->var, ft_strlen(to_check)))
			return (free(to_check), env);
		free(to_check);
		env = env->next;
	}
	return (env);
}

void	push_back_env(t_env *env, char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->next = NULL;
	while (env->next)
		env = env->next;
	new->var = ft_strdup(str);
	if (!new->var)
		return (free(new));
	env->next = new;
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
