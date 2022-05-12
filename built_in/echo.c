/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:25:03 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/12 15:10:20 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_echo(char **av, int fd_out)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (ac > 1)
	{
		if (ft_strncmp(av[1], "-n", 3))
		{
			i++;
			nl = 0;
		}
		while (i < ac)
		{
			ft_putstr_fd(av[i], fd_out);
			if (i + 1 != ac)
				fd_putchar_fd(' ', fd_out);
			i++;
		}
	}
	if (nl)
		fd_putchar_fd('\n',fd_out);
	return (0);
}
