/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:51:19 by mchassig          #+#    #+#             */
/*   Updated: 2022/03/01 17:28:49 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

# define BUFFER_SIZE 1

typedef struct cmd
{
	char	**cmd;
	char	*bin;
	int		fd_read;
	int		fd_write;
}	t_cmd;

// parsing.c
char	**ft_getpaths(char **envp);
void	ft_error_mgt(char *str, int err);
t_cmd	*ft_parsing(int argc, char **argv, char **paths, int *ret);

// struct.c
void	ft_freecmd(t_cmd *cmd);
t_cmd	*ft_setcmd(char *infile, int argc);

// pipex_utils.c
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strcat(char *dest, char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	**ft_split(char const *s, char c);
void	ft_free_split(char **s);

char	*get_next_line(int fd);

#endif
