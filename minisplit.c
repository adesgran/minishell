/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:21:40 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/16 18:34:17 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	static_count_str(char *str)
{
	int		res;
	char	c;

	res = 1;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (str[0] == '\\' && str[1])
			str += 2;
		if (*str == '|')
			res++;
		if (*str == '\"' || *str == '\'')
		{
			c = *str;
			str++;
			while (*str != c && *str)
				str++;
			if (!*str)
				return (0);
		}
		str++;
	}
	return (res);
}

static int	static_line_size(char *str, int res)
{
	char	c;

	res = 0;
	while (*str && *str != '|')
	{
		if (*str == '\\')
		{
			str += 2;
			res += 2;
		}
		if (*str == '\'' || *str == '\"')
		{
			c = *str;
			str++;
			res++;
			while (*str && *str != c)
			{
				str++;
				res++;
			}
		}
		res++;
		str++;
	}
	return (res);
}

static char	*static_next_line(char **str)
{
	int		size;
	int		i;
	char	*res;

	size = static_line_size(*str, 0);
	if (!size)
		return (NULL);
	res = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		res[i] = **str;
		(*str)++;
		i++;
	}
	res[i] = '\0';
	if (**str == '|')
		(*str)++;
	return (res);
}

char	**split_pipes(char *str)
{
	char	**res;
	int		size;
	int		i;

	size = static_count_str(str);
	if (!size)
		return (NULL);
	res = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		res[i] = static_next_line(&str);
		if (!res[i])
		{
			while (--i >= 0)
				free(res[i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	res[size] = NULL;
	return (res);
}
