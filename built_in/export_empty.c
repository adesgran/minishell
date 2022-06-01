/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:15:32 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/01 13:05:03 by adesgran         ###   ########.fr       */
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

void	export_empty(t_env *env, int fd_out)
{
	t_env	*tmp;
	t_env	*new;
	int		size;

	new = duplicate_env(env);
	size = env_size(new);
	while (size)
	{
		tmp = get_lower(new);
		ft_putstr_fd("export ", fd_out);
		ft_putstr_fd(tmp->var, fd_out);
		ft_putstr_fd("=", fd_out);
		ft_putstr_fd(tmp->value, fd_out);
		ft_putchar_fd('\n', fd_out);
		new = remove_var_env(new, tmp->var);
		size--;
	}
}
