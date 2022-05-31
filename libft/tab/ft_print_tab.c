/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:32:40 by adesgran          #+#    #+#             */
/*   Updated: 2022/01/09 12:42:20 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_print_tab(int **tab, int n_col, int n_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_line)
	{
		j = 0;
		while (j < n_col)
		{
			ft_printf("%d\t", tab[i][j]);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}
