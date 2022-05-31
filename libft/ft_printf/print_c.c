/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <adesgran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:04:27 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:43:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(va_list args)
{
	int				c;
	unsigned char	r;

	c = va_arg(args, int);
	r = (unsigned char)c;
	write(1, &r, 1);
	return (1);
}
