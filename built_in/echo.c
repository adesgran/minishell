/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:25:03 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/25 12:39:16 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_flag(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) < 2)
		return (0);
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str += 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	mini_echo(char **av)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (av[i])
	{
		while (is_valid_flag(av[i]))
		{
			if (is_valid_flag(av[i]))
				nl = 0;
			i++;
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
