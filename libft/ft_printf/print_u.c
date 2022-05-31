/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <adesgran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:37:16 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:43:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h" 

static int	ft_putunsigned(va_list args)
{
	unsigned int	i;
	unsigned int	dec;
	int				res;

	i = va_arg(args, unsigned int);
	res = 0;
	dec = 1000000000;
	while (dec && i / dec == 0)
		dec /= 10;
	if (dec == 0)
	{
		res++;
		ft_putchar_fd('0', 1);
	}
	while (dec)
	{
		ft_putchar_fd('0' + (i / dec), 1);
		i = i % dec;
		dec /= 10;
		res++;
	}
	return (res);
}

int	print_u(va_list args)
{
	return (ft_putunsigned(args));
}
