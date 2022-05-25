/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:22:42 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/25 15:35:39 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_len(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (ft_strlen(str + i) > 2)
	{
		if (ft_strncmp(str + i, "/./", 3) == 0 || \
				ft_strncmp(str + i, "/.", 3) == 0)
		{
			i += 2;
		}
		else
		{
			i++;
			res++;
		}
	}
	return (res);
}



static char	*fix_str(char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (count_len(str) + 1));
	i = 0;
	while (*str)
	{
		if (ft_strlen(str) >= 2 && (ft_strncmp(str, "/./", 3) == 0 || \
				ft_strncmp(str, "/.", 3) == 0))
			str += 2;
		else
		{
			res[i] = *str;
			str++;
			i++;
		}
	}
	res[i] = '\0';
	return (res);
}

char	*formate_pwd_bis(char *str)
{
	char	*res;

	if (!str)
		return (str);
	res = fix_str(str);
	free(str);
	return (res);
}

