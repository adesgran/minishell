/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:08:49 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:29:13 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_ison(char c, char const *s)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

static int	ft_getbegin(char const *s1, char const *set)
{
	int	begin;

	begin = 0;
	while (ft_ison(s1[begin], set) && s1[begin])
		begin++;
	return (begin);
}

static int	ft_getend(char const *s1, char const *set)
{
	int	end;
	int	i;

	end = 0;
	i = 0;
	while (s1[i])
	{
		if (!ft_ison(s1[i], set))
			end = i;
		i++;
	}
	if (end == 0)
		return (i);
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		begin;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	begin = ft_getbegin(s1, set);
	end = ft_getend(s1, set);
	res = malloc(sizeof(char) * (end - begin + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (i + begin <= end)
	{
		res[i] = s1[begin + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
