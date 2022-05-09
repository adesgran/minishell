/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:51:38 by mchassig          #+#    #+#             */
/*   Updated: 2022/03/01 17:29:33 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_getpaths(char **envp)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")) != 0)
		i++;
	if (!envp[i])
		exit(128);
	tmp = ft_substr(envp[i], ft_strlen("PATH="), ft_strlen(envp[i]));
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	free(tmp);
	return (paths);
}

void	ft_getbin(char **paths, t_cmd *cmd, int j, int size)
{
	int		i;
	int		len;

	i = 0;
	if (!cmd[j].cmd[0])
		return (ft_error_mgt(cmd[j].cmd[0], 2));
	while (paths[i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(cmd[j].cmd[0]) + 1;
		cmd[j].bin = malloc(sizeof(char) * (len + 1));
		if (!cmd[j].bin)
			return ;
		cmd[j].bin[0] = '\0';
		cmd[j].bin = ft_strcat(cmd[j].bin, paths[i]);
		cmd[j].bin = ft_strcat(cmd[j].bin, "/");
		cmd[j].bin = ft_strcat(cmd[j].bin, cmd[j].cmd[0]);
		if (access(cmd[j].bin, X_OK) == 0)
			break ;
		free(cmd[j].bin);
		cmd[j].bin = NULL;
		i++;
	}
	if (!paths[i] && ((j != 0 || cmd[0].fd_read != -1)
			&& (j != size - 1 || cmd[size - 1].fd_write != -1)))
		ft_error_mgt(cmd[j].cmd[0], 2);
}

int	ft_here_doc(t_cmd *cmd, char *argv)
{
	char	*line;
	char	*limiter;

	limiter = malloc(sizeof(char) * (ft_strlen(argv) + 2));
	if (!limiter)
		return (-1);
	limiter[0] = '\0';
	limiter = ft_strcat(limiter, argv);
	limiter = ft_strcat(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (-1);
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0)
			break ;
		ft_putstr_fd(line, cmd[0].fd_read);
		free(line);
		line = NULL;
	}
	free(line);
	free(limiter);
	close(cmd[0].fd_read);
	return (0);
}

int	ft_getfd(char **argv, int argc, t_cmd *cmd, int *ret)
{
	int	len;

	len = argc - 4;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc > 5)
	{
		len--;
		cmd[0].fd_read = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (ft_here_doc(cmd, argv[2]) == -1)
			return (-1);
	}
	cmd[0].fd_read = open(argv[1], O_RDONLY);
	if (cmd[0].fd_read == -1)
		ft_error_mgt(argv[1], 1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc > 5)
		cmd[len].fd_write = open(argv[argc -1], 2 | 1024 | 64, 0644);
	else
		cmd[len].fd_write = open(argv[argc -1], 2 | 512 | 64, 0644);
	if (cmd[len].fd_write == -1)
		*ret = 1;
	return (len + 1);
}

t_cmd	*ft_parsing(int argc, char **argv, char **paths, int *ret)
{
	t_cmd	*cmd;
	int		i;
	int		size;

	cmd = ft_setcmd(argv[1], argc);
	if (!paths || !cmd)
		return (ft_free_split(paths), ft_freecmd(cmd), NULL);
	size = ft_getfd(argv, argc, cmd, ret);
	if (size < 0)
		return (ft_free_split(paths), ft_freecmd(cmd), NULL);
	i = -1;
	while (++i < size)
	{
		cmd[i].cmd = ft_split(argv[i + argc - size - 1], ' ');
		if (!cmd[i].cmd)
			return (ft_free_split(paths), ft_freecmd(cmd), NULL);
		ft_getbin(paths, cmd, i, size);
		if (!cmd[i].bin && *ret != 1)
			*ret = 127;
	}
	if (cmd[size - 1].fd_write == -1)
		ft_error_mgt(argv[argc - 1], 3);
	if (cmd[size - 1].bin && *ret != 1)
		*ret = 0;
	return (ft_free_split(paths), cmd);
}
