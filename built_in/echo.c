/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:25:03 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 19:35:00 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_echo(char **av, int fd_out)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	ft_putstr_fd("bienvenue dans echo !\n", fd_out);
	if (av[i])
	{
		if (ft_strncmp(av[1], "-n", 3))
		{
			i++;
			nl = 0;
		}
		while (av[i])
		{
			ft_putstr_fd(av[i], fd_out);
			if (av[i + 1])
				ft_putchar_fd(' ', fd_out);
			i++;
		}
	}
	if (nl)
		ft_putchar_fd('\n', fd_out);
	return (0);
}
