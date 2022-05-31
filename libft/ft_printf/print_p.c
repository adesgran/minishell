/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <adesgran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:45:28 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:43:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h" 

static int	get_length(unsigned long int nb)
{
	int	res;

	res = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		res++;
		nb = nb / 16;
	}
	return (res);
}

static char	to_hex(unsigned int i)
{
	if (i < 10)
		return (i + '0');
	else
		return (i - 10 + 'a');
}

static unsigned long int	get_pt(va_list args)
{
	unsigned long int	nb;
	void				*pt;

	pt = va_arg(args, void *);
	nb = (unsigned long int)pt;
	return (nb);
}

static int	print_nil(void)
{
	write(1, "0x0", 3);
	return (3);
}

int	print_p(va_list args)
{
	unsigned long int	nb;
	char				*s;
	int					i;
	int					res;

	nb = get_pt(args);
	if (!nb)
		return (print_nil());
	i = get_length(nb) + 2;
	res = i;
	s = malloc(sizeof(char) * (i + 3));
	if (!s)
		return (0);
	s[0] = '0';
	s[1] = 'x';
	s[i] = '\0';
	while (i > 2)
	{
		i--;
		s[i] = to_hex(nb % 16);
		nb = nb / 16;
	}
	ft_putstr_fd(s, 1);
	free(s);
	return (res);
}
