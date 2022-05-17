/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:25:03 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/17 17:33:20 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_echo(char **av)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (av[i])
	{
		if (ft_strncmp(av[1], "-n", 3) == 0)
		{
			i++;
			nl = 0;
		}
		while (av[i])
		{
			ft_putstr_fd(av[i], STDOUT_FILENO);
			if (av[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
