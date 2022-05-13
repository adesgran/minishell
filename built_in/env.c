/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:11:39 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 16:07:58 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_env(t_data *data, int fd_out)
{
	t_env	*env;

	if (!data || fd_out < 1)
		return (1);
	env = data->env;
	while (env)
	{
		ft_putstr_fd(env->var, fd_out);
		ft_putstr_fd("=", fd_out);
		ft_putstr_fd(env->var, fd_out);
		ft_putchar_fd('\n', fd_out);
		env = env->next;
	}
	return (0);
}
