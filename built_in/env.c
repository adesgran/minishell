/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:11:39 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/12 15:16:11 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env(t_data *data, int fd_out)
{
	if (!data || fd_out < 1)
		return (1);
	while (data)
	{
		ft_putstr_fd(data->var, fd_out);
		ft_putchar_fd('\n', fd_out);
		data = data->next;
	}
	return (0);
}
