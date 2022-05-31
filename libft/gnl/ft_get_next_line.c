/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <adesgran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:11:52 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/26 17:22:52 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

static char	*strjoin_free(char *s1, char *s2)
{
	int			i;
	int			j;
	size_t		len;
	char		*res;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	free(s2);
	return (res);
}

static char	*read_buffer(char **buffer)
{
	char	*res;
	char	*new_buff;
	int		next;
	int		len;

	if (*buffer == NULL)
		return (NULL);
	len = ft_strlen(*buffer);
	next = next_nl(*buffer);
	if (next == -1)
	{
		res = ft_strndup(*buffer, ft_strlen(*buffer));
		new_buff = NULL;
	}
	else
	{
		res = ft_strndup(*buffer, next + 1);
		new_buff = ft_strndup(*buffer + next + 1, len);
	}
	free(*buffer);
	*buffer = new_buff;
	return (res);
}

static char	*fill_buffer(char *s, char **buff)
{
	int		len;
	int		len_s;
	char	*res;

	if (!s || !buff)
		return (NULL);
	len = next_nl(s);
	len_s = ft_strlen(s);
	res = ft_strndup(s, len + 1);
	if (len_s > len + 1)
	{
		*buff = ft_strndup(s + len + 1, len_s - len + 1);
		if (!buff)
		{
			free(res);
			free(s);
			return (NULL);
		}
	}
	free(s);
	return (res);
}

static char	*fill_line(int fd, char *s, char **buff)
{
	char	*buffer;
	int		n_char;
	char	*temp;

	buffer = malloc(sizeof(char) * ((long)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	n_char = read(fd, buffer, BUFFER_SIZE);
	if (n_char <= 0)
	{
		free(*buff);
		free(buffer);
		if (n_char == 0)
			return (s);
		free(s);
		return (NULL);
	}
	buffer[n_char] = '\0';
	if (next_nl(buffer) == -1)
		temp = fill_line(fd, strjoin_free(s, buffer), buff);
	else
		temp = strjoin_free(s, fill_buffer(buffer, buff));
	return (temp);
}

char	*ft_get_next_line(int fd)
{
	static char	*stat_buff[1024];
	char		*line;

	if (fd < 0 || fd > 1023)
		return (NULL);
	if (stat_buff[fd])
		line = read_buffer(&stat_buff[fd]);
	else
		line = ft_strndup("", 1);
	if (!line)
		return (NULL);
	if (next_nl(line) == -1)
		line = fill_line(fd, line, &stat_buff[fd]);
	if (!line)
		return (NULL);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
