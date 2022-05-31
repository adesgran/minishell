/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:48:29 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:43:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_arg(char c, va_list args)
{
	if (c == 'c')
		return (print_c(args));
	if (c == 's')
		return (print_s(args));
	if (c == 'i')
		return (print_i(args));
	if (c == 'd')
		return (print_d(args));
	if (c == 'x')
		return (print_x(args));
	if (c == 'X')
		return (print_upx(args));
	if (c == 'p')
		return (print_p(args));
	if (c == 'u')
		return (print_u(args));
	return (0);
}

int	write_sign(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s == '%')
				count += write_sign();
			else
				count += print_arg(*s, args);
		}
		else
		{
			ft_putchar_fd(*s, 1);
			count++;
		}
		s++;
	}
	return (count);
}
