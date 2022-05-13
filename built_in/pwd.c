/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:32:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 16:40:18 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_pwd(t_data *data, int fd_out)
{
	t_env	*pwd;

	pwd = get_var_env(data, "PWD");
	if (!pwd)
		return (1);
	ft_putstr_fd(pwd->value, fd_out);
	return (0);
}
