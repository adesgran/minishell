/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <adesgran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:12:24 by adesgran          #+#    #+#             */
/*   Updated: 2022/01/09 17:53:00 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	if (!str)
		return (0);
	while (*str == '\t' || *str == '\n' || *str == '\r' || \
			*str == '\v' || *str == '\f' || *str == ' ')
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while (ft_isdigit(*str))
	{
		res = 10 * res + sign * (*str - '0');
		str++;
	}
	return (res);
}
