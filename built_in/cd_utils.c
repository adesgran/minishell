/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:44:36 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/25 15:48:35 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_len(char *str)
{
	int	res;
	int	i;
	int	j;

	res = 0;
	i = 0;
	while (str[i] && ft_strlen(str + i) > 2)
	{
		if (ft_strncmp(str + i, "/..", 3) == 0)
		{
			//res--;
			j = -1;
			while (str[i + j] != '/' && str[i + j])
			{
				j--;
				res--;
			}
			i += 3;
			break ;
		}
		i++;
		res++;
	}
	return (res + ft_strlen(str));
}



static char	*fix_str(char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (count_len(str) + 1));
	i = 0;
	while (*str)
	{
		if (ft_strlen(str) > 2 && ft_strncmp(str, "/..", 3) == 0)
		{
			i--;
			while (res[i] != '/')
				i--;
			str += 3;
			break ;
		}
		res[i] = *str;
		str++;
		i++;
	}
	while (*str)
	{
		res[i] = *str;
		str++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	need_change(char *str)
{
	if (!str)
		return (0);
	while (ft_strlen(str) > 2)
	{
		if (ft_strncmp(str, "/..", 3) == 0)
			return (1);
		str++;
	}
	return (0);
}

char	*formate_pwd(char *str)
{
	char	*new;

	str = formate_pwd_bis(str);
	if (!str)
		return (str);
	while (need_change(str))
	{
		new = fix_str(str);
		free(str);
		str = new;
	}
	return (str);
}
