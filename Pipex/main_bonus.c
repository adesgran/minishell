/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:56:07 by mchassig          #+#    #+#             */
/*   Updated: 2022/03/04 17:49:03 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error_mgt(char *str, int err)
{
	if (err == 1)
		perror(str);
	else
	{
		ft_putstr_fd(str, 2);
		if (err == 2)
			ft_putstr_fd(": command not found\n", 2);
		else if (err == 3)
			ft_putstr_fd(": Permission denied\n", 2);
	}
}

int	ft_setpipefd(int size, t_cmd *cmd)
{
	int	pipefd[2];
	int	i;

	i = 0;
	while (i < size)
	{
		if (pipe(pipefd) == -1)
			return (-1);
		if (cmd[i + 1].fd_read == -1)
			cmd[i + 1].fd_read = pipefd[0];
		if (cmd[i].fd_write == -1)
			cmd[i].fd_write = pipefd[1];
		i++;
	}
	return (0);
}

int	ft_exec_cmd(t_cmd *cmd, int i, int size, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_freecmd(cmd), perror("fork"), -1);
	else if (pid == 0)
	{
		if (i < size - 1)
			close(cmd[i + 1].fd_read);
		dup2(cmd[i].fd_read, STDIN_FILENO);
		close(cmd[i].fd_read);
		dup2(cmd[i].fd_write, STDOUT_FILENO);
		close(cmd[i].fd_write);
		if (cmd[i].fd_read != -1)
			execve(cmd[i].bin, cmd[i].cmd, envp);
		exit(EXIT_SUCCESS);
	}
	if (i < size - 1)
		close(cmd[i].fd_write);
	if (i != 0)
		close(cmd[i].fd_read);
	return (pid);
}

void	ft_pipex(t_cmd *cmd, char **envp, int size)
{
	int		i;
	int		status;

	i = 0;
	if (ft_setpipefd(size, cmd) == -1)
		return ;
	while (i < size)
	{
		if (ft_exec_cmd(cmd, i, size, envp) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	status = 0;
	while (--i > 0)
		wait(&status);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	int		ret;
	int		size;

	if (argc < 5)
		return (-1);
	ret = 0;
	cmd = ft_parsing(argc, argv, ft_getpaths(envp), &ret);
	if (ret == 1 || !cmd)
		return (ft_freecmd(cmd), ret);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc > 5)
		size = argc - 4;
	else
		size = argc - 3;
	ft_pipex(cmd, envp, size);
	if (size == argc - 4)
		unlink("here_doc");
	return (ft_freecmd(cmd), ret);
}
