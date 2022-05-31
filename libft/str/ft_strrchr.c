/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:10:25 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/01 13:14:50 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strrchr(const char *s, int c)
{
	char		c2;
	const char	*res;

	c2 = (char)c;
	res = NULL;
	while (*s)
	{
		if (*s == c2)
			res = s;
		s++;
	}
	if (!c2)
		res = s;
	return ((char *)res);
}
