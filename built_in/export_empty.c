/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:15:32 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/31 14:56:54 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	env_size(t_env *env)
{
	if (env->next)
		return (env_size(env->next) + 1);
	return (1);
}

static t_env	*get_lower(t_env *env)
{
	char	*curr;
	t_env	*res;

	res = env;
	curr = env->var;
	while (env->next)
	{
		env = env->next;
		if (ft_strcmp(curr, env->var) > 0 && env)
		{
			res = env;
			curr = env->var;
		}
	}
	return (res);
}

void	export_empty(t_env *env)
{
	t_env	*tmp;
	int		size;

	size = env_size(env);
	while (size)
	{
		tmp = get_lower(env);
		printf("export %s=%s\n", tmp->var, tmp->value);
		env = remove_var_env(env, tmp->var);
		size--;
	}
}
