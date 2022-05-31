/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <adesgran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:49:40 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/01 13:13:06 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strchr(const char *s, int c)
{
	char	c2;

	c2 = (char)c;
	while (*s != c2 && *s)
		s++;
	if (*s == c2)
		return ((char *)s);
	return (NULL);
}
