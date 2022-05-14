/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:32:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 19:31:47 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_pwd(t_data *data, int fd_out)
{
	t_env	*pwd;

	pwd = get_var_env(data->env, "PWD");
	if (!pwd)
		return (1);
	ft_putstr_fd(pwd->value, fd_out);
	return (0);
}
