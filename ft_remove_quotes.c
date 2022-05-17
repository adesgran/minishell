/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:10:10 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/17 15:05:56 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_size_inquotes(char *str, int *i, int *res)
{
	char	sep;

	sep = str[*i];
	*i += 1;
	while (str[*i] && str[*i] != sep)
	{
		if (str[*i] == '\\' && str[*i + 1] == sep)
			*i += 2;
		else
			*i += 1;
		*res += 1;
	}
	if (!str[*i])
		return (1);
	*i += 1;
	return (0);
}

static int	get_size(char *str)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i += 2;
			res++;
		}
		else if (str[i] == '\"' || str[i] == '\'')
		{
			if (get_size_inquotes(str, &i, &res))
					return (0);
		}
		else
		{
			i++;
			res++;
		}
	}
	return (res);
}

static void	fill_str_inquotes(char **res, char **str)
{
	char	sep;

	sep = **str;
	*str += 1;
	while (**str && **str != sep)
	{
		if (str[0][0] == '\\' && str[0][1] == sep)
		{
			res[0][0] = str[0][1];
			*res += 1;
			*str += 2;
		}
		else
		{
			res[0][0] = str[0][0];
			*res += 1;
			*str += 1;
		}
	}
	*str += 1;
}

static void	fill_str(char *res, char *str)
{
	while (*str)
	{
		if (str[0] == '\\' && str[1])
		{
			*res = str[1];
			str += 2;
			res++;
		}
		else if (*str == '\"' || *str == '\'')
			fill_str_inquotes(&res, &str);
		else
		{
			*res = *str;
			res++;
			str++;
		}
	}
}

char	*ft_remove_quotes(char *str)
{
	int		size;
	char	*res;

	size = get_size(str);
	if (!size)
		return (NULL);
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	fill_str(res, str);
	return (res);
}
