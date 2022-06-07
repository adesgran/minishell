/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:21:40 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/07 18:32:14 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	static_count_str(char *str)
{
	int		res;
	char	c;

	res = 1;
	c = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str == '\\' && str[1])
			str++;
		else if (*str == '|' && c == 0 && str[1])
			res++;
		else if (*str == c)
			c = 0;
		else if ((*str == '\"' || *str == '\'') && c == 0)
			c = *str;
		str++;
	}
	return (res);
}

static int	static_line_size(char *str)
{
	char	c;
	int		size;

	size = 0;
	c = 0;
	while (*str)
	{
		if (*str == '\\' && str[1])
		{
			str++;
			size++;
		}
		else if (*str == '|' && c == 0)
			break ;
		else if (*str == c)
			c = 0;
		else if ((*str == '\'' || *str == '\"') && c == 0)
			c = *str;
		size++;
		str++;
	}
	if (*str)
		size++;
	return (size);
}

static char	*static_next_line(char **str, int *ret)
{
	int		size;
	int		i;
	char	*res;

	size = static_line_size(*str);
	if (!size)
		return (NULL);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = **str;
		(*str)++;
		i++;
	}
	res[i] = '\0';
	(void)ret;
	return (res);
}

char	**split_pipes(char *str, int *ret)
{
	char	**res;
	int		size;
	int		i;
	char	*cpy;

	cpy = str;
	size = static_count_str(str);
	if (!str)
		return (free(cpy), NULL);
	res = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		res[i] = static_next_line(&str, ret);
		if (!res[i])
		{
			while (--i >= 0)
				free(res[i]);
			free(res);
			return (free(cpy), NULL);
		}
		i++;
	}
	res[size] = NULL;
	return (free(cpy), res);
}
