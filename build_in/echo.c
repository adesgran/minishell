/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:25:03 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/11 18:34:09 by adesgran         ###   ########.fr       */
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
			printf("%s", av[i]);
			if (i + 1 != ac)
				printf(" ");
			i++;
		}
	}
	if (nl)
		printf("\n");
	return (0);
}
