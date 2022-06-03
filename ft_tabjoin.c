/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:29:03 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/03 12:21:02 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_destlen(int size, char **strs, char *sep)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j])
			j++;
		len += j;
		i++;
	}
	i = 0;
	while (sep[i])
		i++;
	len = len + i * (size - 1);
	return (len);
}

static int	ft_copy(char *dest, char *src, int i)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	return (i);
}

static int	ft_tablen(char **strs)
{
	if (*strs)
		return (ft_tablen(strs + 1) + 1);
	return (0);
}

char	*ft_tabjoin(char **strs, char *sep)
{
	char	*dest;
	int		i;
	int		l;
	int		len;
	int		size;

	size = ft_tablen(strs);
	if (!size)
		return (NULL);
	len = ft_destlen(size, strs, sep);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	l = 0;
	while (i < size)
	{
		l = ft_copy(dest, strs[i], l);
		i++;
		if (i < size)
			l = ft_copy(dest, sep, l);
	}
	dest[l] = '\0';
	return (dest);
}
