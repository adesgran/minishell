/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:01:06 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/27 12:07:38 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	env_size(t_env *env)
{
	if (env)
		return (env_size(env->next) + 1);
	return (1);
}

char	**env_to_tab(t_env *env)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (env)
	{
		res[i] = ft_strjoinx(3, env->var, "=", env->value);
		if (!res[i])
			return (ft_free_tabstr(res), NULL);
		env = env->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
