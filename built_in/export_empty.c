/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:15:32 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/02 16:48:43 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	export_empty(t_data *data)
{
	t_env	*tmp;
	t_env	*env;

	env = data->env;
	while (env)
	{
		tmp = get_lower(env);
		printf("export %s=\"%s\"\n", tmp->var, tmp->value);
		env = remove_var_env(env, tmp->var);
	}
	data->env = NULL;
}
