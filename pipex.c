/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:29:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/11 14:31:22 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	close_other(t_data	*data, t_cmd *cmd)
{
	t_cmd	*temp;

	temp = data->cmd;
	while (temp)
	{
		if (temp != cmd)
		{
			if (temp->fd_infile > 2)
				close(temp->fd_infile);
			if (temp->fd_outfile > 2)
				close(temp->fd_outfile);
		}
		temp = temp->next;
	}
}

static int	exec_cmd(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Fork"), 1);
	if (!pid)
	{
		close_other(data, cmd);
		dup2(cmd->fd_infile, STDIN_FILENO);
		if (cmd->fd_infile > 2)
			close(cmd->fd_infile);
		dup2(cmd->fd_outfile, STDOUT_FILENO);
		if (cmd->fd_outfile > 2)
			close(cmd->fd_outfile);
		execve(cmd->bin_path, cmd->cmd, data->envp);
	}
	return (pid);
}

static void	close_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->fd_infile > 2)
			close(cmd->fd_infile);
		if (cmd->fd_outfile > 2)
			close(cmd->fd_outfile);
		cmd = cmd->next;
	}
}

int	set_pipefd(t_cmd *cmd)
{
	int		pipefd[2];
	t_cmd	*cmd_init;

	cmd_init = cmd;
	while (cmd)
	{
		if (cmd->fd_infile == -2)
			cmd->fd_infile = 0;
		if (cmd->next)
		{
			if (pipe(pipefd) == -1)
			{
				close_pipes(cmd_init);
				return (1);
			}
			if (cmd->fd_outfile == -2)
				cmd->fd_outfile = pipefd[1];
			if (cmd->next->fd_infile == -2)
				cmd->next->fd_infile = pipefd[0];
		}
		if (!cmd->next && cmd->fd_outfile == -2)
			cmd->fd_outfile = 1;
		cmd = cmd->next;
	}
	return (0);
}

void	pipex(t_data *data)
{
	int		status;
	size_t	i;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd;
	set_pipefd(cmd);
	while (cmd)
	{
		i++;
		exec_cmd(data, cmd);
		cmd = cmd->next;
	}
	status = 0;
	while (--i)
		wait(&status);
	close_pipes(data->cmd);
}
