/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:25:03 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/12 12:27:01 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av)
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
			write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
			if (i + 1 != ac)
				write(STDOUT_FILENO, " ", 1);
			i++;
		}
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
