/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <adesgran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:35:44 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:43:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h" 

static int	printnbr(int n)
{
	int	dec;
	int	res;

	dec = 1000000000;
	res = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n = -1 * n;
		res++;
	}
	while (n / dec == 0 && dec)
		dec /= 10;
	while (dec)
	{
		ft_putchar_fd((n / dec) + '0', 1);
		n = n % dec;
		dec /= 10;
		res++;
	}
	return (res);
}

int	print_d(va_list args)
{
	int	i;

	i = va_arg(args, int);
	if (i == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (11);
	}
	if (i == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	return (printnbr(i));
}
