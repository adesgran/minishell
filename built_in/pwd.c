/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:32:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/17 18:15:12 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_pwd(t_data *data)
{
	t_env	*pwd;

	pwd = get_var_env(data->env, "PWD");
	if (!pwd)
		return (1);
	ft_putstr_fd(pwd->value, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
