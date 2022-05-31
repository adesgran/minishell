/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:11:05 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/27 14:35:44 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_first_size(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static char	*fill_begin(char *str, char c)
{
	int		i;
	char	*res;

	res = malloc(sizeof(char) * (get_first_size(str, c) + 1));
	if (!res)
		return (res);
	i = 0;
	while (str[i] != c && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**ft_split_first(char *str, char c)
{
	char	**res;

	res = malloc(sizeof(char *) * 3);
	if (!res)
		return (res);
	res[0] = fill_begin(str, c);
	if (!res[0])
		return (free(res), NULL);
	res[1] = ft_strdup(str + get_first_size(str, c) + 1);
	if (!res[1])
		return (free(res[0]), free(res), NULL);
	res[2] = NULL;
	return (res);
}
