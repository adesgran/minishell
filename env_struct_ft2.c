/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_ft2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:30:12 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/02 12:18:22 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_env	*free_temp_env(t_env *env)
{
	if (env->var)
		free(env->var);
	if (env->value)
		free(env->value);
	free(env);
	return (NULL);
}

t_env	*init_empty_env(void)
{
	t_env	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	res->var = ft_strdup("PWD");
	res->value = malloc(sizeof(char) * 201);
	getcwd(res->value, 200);
	if (!res->var || !res->value)
		return (free_temp_env(res));
	res->next = malloc(sizeof(*res));
	if (!res->next)
		return (res);
	res->next->var = ft_strdup("SHLVL");
	res->next->value = ft_strdup("0");
	if (!res->next->var || !res->next->value)
	{
		res->next = free_temp_env(res->next);
		return (res);
	}
	res->next->next = NULL;
	push_back_env(res, "PWD", NULL);
	push_back_env(res, "OLD_PWD", NULL);
	return (res);
}
