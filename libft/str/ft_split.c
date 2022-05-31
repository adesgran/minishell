/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:16:16 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:29:13 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_next_length(char const *s, char c)
{
	size_t	res;

	res = 0;
	while (s[res] != c && s[res])
		res++;
	return (res);
}

static size_t	ft_count_part(char const *s, char c)
{
	size_t	res;
	size_t	i;

	res = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			res++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c && s[i])
			i++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**res;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_count_part(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			res[j] = ft_strndup(s + i, ft_next_length(s + i, c));
			if (!res[j++])
				return (NULL);
			i += ft_next_length(s + i, c);
		}
		while (s[i] == c && s[i])
			i++;
	}
	res[j] = NULL;
	return (res);
}
