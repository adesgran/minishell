/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:21:07 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/01 13:57:18 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	size_t			i;
	unsigned char	uc;

	uc = (unsigned char)c;
	temp = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (temp[i] == uc)
			return ((unsigned char *)s + i);
		i++;
	}
	return (NULL);
}
