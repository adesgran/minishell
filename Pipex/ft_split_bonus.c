/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:19:50 by mchassig          #+#    #+#             */
/*   Updated: 2022/02/23 14:40:34 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	word_count(char const *s, char c)
{
	int	i;
	int	wrd;

	if (s[0] == '\0')
		return (0);
	i = 0;
	wrd = 0;
	while (s[++i])
		if (s[i] == c && s[i - 1] != c)
			wrd++;
	if (s[i - 1] != c)
		wrd++;
	return (wrd);
}

static int	letter_count(char const *s, char c, int i)
{
	int	ltr;

	ltr = 0;
	while (s[i + ltr] && s[i + ltr] != c)
		ltr++;
	return (ltr);
}

static char	*ft_substr_split(char const *s, int *i, int ltr)
{
	char	*str;
	int		k;

	str = malloc(sizeof(char) * (ltr + 1));
	if (!str)
		return (NULL);
	k = 0;
	while (k < ltr)
	{
		str[k] = s[*i];
		k++;
		*i = *i + 1;
	}
	str[k] = '\0';
	return (str);
}

void	ft_free_split(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	int		wrd;
	int		i;
	int		j;
	char	**dest;

	if (!s)
		return (NULL);
	wrd = word_count(s, c);
	dest = malloc(sizeof(char *) * (wrd + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	while (j < wrd)
	{
		if (letter_count(s, c, ++i) != 0)
		{
			dest[j] = ft_substr_split(s, &i, letter_count(s, c, i));
			if (!dest[j])
				return (ft_free_split(dest), NULL);
			j++;
		}
	}
	dest[j] = NULL;
	return (dest);
}
