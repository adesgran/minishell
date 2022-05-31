/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:13:48 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:29:13 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	res;

	if (ft_strlen(dst) >= dstsize)
	{
		res = ft_strlen(src) + dstsize;
		return (res);
	}
	else
		res = ft_strlen(dst) + ft_strlen(src);
	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (i + 1 < dstsize && src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (res);
}
