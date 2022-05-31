/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_topx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:06:29 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:43:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_length(unsigned int nb)
{
	int	res;

	res = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		res++;
		nb = nb / 16;
	}
	return (res);
}

static char	to_hex_min(int i)
{
	if (i < 10)
		return (i + '0');
	else
		return (i - 10 + 'A');
}

static int	print_topx(unsigned int nb)
{
	char	*s;
	int		i;
	int		res;

	i = get_length(nb);
	res = i;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (0);
	s[i] = '\0';
	while (i > 0)
	{
		i--;
		s[i] = to_hex_min(nb % 16);
		nb = nb / 16;
	}
	ft_putstr_fd(s, 1);
	free(s);
	return (res);
}

int	print_upx(va_list args)
{
	unsigned int	nb;

	nb = va_arg(args, unsigned int);
	return (print_topx(nb));
}
