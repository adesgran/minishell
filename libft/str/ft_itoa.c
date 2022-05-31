/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:26:58 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:29:13 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_get_size(int n)
{
	int	res;

	res = 1;
	if (n < 0)
		res += 1;
	while (n > 9 || n < -9)
	{
		res += 1;
		n /= 10;
	}
	return (res);
}

static void	ft_fill(char *s, int n)
{
	size_t	i;
	int		dec;

	dec = 1000000000;
	i = 0;
	if (n == 0)
	{
		s[0] = '0';
		s[1] = '\0';
		return ;
	}
	while (dec && n / dec == 0)
		dec /= 10;
	while (dec)
	{
		s[i] = (n / dec) + '0';
		n = n % dec;
		dec /= 10;
		i++;
	}
	s[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*res;
	int		temp;

	res = malloc(sizeof(char) * (ft_get_size(n) + 1));
	if (!res)
		return (NULL);
	temp = 0;
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		n = 147483648;
		temp = 2;
	}
	if (n < 0)
	{
		res[temp] = '-';
		n = -1 * n;
		temp++;
	}
	ft_fill(res + temp, n);
	return (res);
}
