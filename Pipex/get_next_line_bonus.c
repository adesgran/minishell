/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:17:48 by mchassig          #+#    #+#             */
/*   Updated: 2022/03/01 13:53:13 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_free_gnl(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		len;
	char	*dest;
	int		j;
	int		i;

	if (!s1)
		return (ft_substr(s2, 0, ft_strlen(s2)));
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (ft_free_gnl(s1, NULL));
	dest[len] = '\0';
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = -1;
	while (s2[++j])
		dest[i + j] = s2[j];
	free(s1);
	return (dest);
}

static int	ft_isend(char *s, int r)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	if (r < BUFFER_SIZE)
		return (ft_strlen(s));
	return (-1);
}

static char	*ft_line(char **s, int i)
{
	char	*ret;
	char	*cpy;

	cpy = *s;
	ret = ft_substr(*s, 0, i);
	if (!ret)
		return (ft_free_gnl(*s, NULL));
	*s = ft_substr(*s, i, ft_strlen(*s));
	if (!*s)
		return (ft_free_gnl(ret, NULL));
	free(cpy);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*s = NULL;
	char		*buf;
	int			r;
	int			i;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ft_free_gnl(s, NULL));
	i = -1;
	while (i == -1)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1 || (r == 0 && ft_strlen(s) == 0))
			return (ft_free_gnl(s, buf));
		buf[r] = '\0';
		s = ft_strjoin_gnl(s, buf);
		if (!s)
			return (ft_free_gnl(buf, NULL));
		i = ft_isend(s, r);
	}
	free(buf);
	return (ft_line(&s, i));
}
