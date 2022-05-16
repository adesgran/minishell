/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:29:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/16 12:47:09 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	close_pipes(t_data	*data, t_cmd *cmd)
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

void	call_built_in(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
	{
		mini_echo(cmd->cmd, cmd->fd_outfile);
	}
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		mini_env(data, cmd->fd_outfile);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		mini_pwd(data, cmd->fd_outfile);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		mini_unset(data, cmd->cmd);
}

static int	exec_cmd(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("Fork"), 1);
	if (!pid)
	{
		dup2(cmd->fd_infile, STDIN_FILENO);
		if (cmd->fd_infile > 2)
			close(cmd->fd_infile);
		dup2(cmd->fd_outfile, STDOUT_FILENO);
		if (cmd->fd_outfile > 2)
			close(cmd->fd_outfile);
		close_pipes(data, cmd);
		if (ft_strncmp(cmd->bin_path, "built_in/", 9) == 0)
			call_built_in(data, cmd);
		else
			execve(cmd->bin_path, cmd->cmd, data->envp);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

int	set_pipefd(t_cmd *cmd, t_data *data)
{
	int		pipefd[2];

	while (cmd)
	{
		if (cmd->fd_infile == -2)
			cmd->fd_infile = 0;
		if (cmd->next)
		{
			if (pipe(pipefd) == -1)
				return (close_pipes(data, NULL), 1);
			if (cmd->next->fd_infile == -2)
				cmd->next->fd_infile = pipefd[0];
			if (cmd->fd_outfile == -2)
				cmd->fd_outfile = pipefd[1];
		}
		else
			if (cmd->fd_outfile == -2)
				cmd->fd_outfile = 1;
		cmd = cmd->next;
	}
	return (0);
}

int	pipex(t_data *data)
{
	int		status;
	size_t	i;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd;
	if (set_pipefd(cmd, data))
		return (-1);
	while (cmd)
	{
		if (cmd->fd_infile != -1 && cmd->fd_outfile != -1 && cmd->bin_path)
		{
			i++;
			exec_cmd(data, cmd);
		}
		cmd = cmd->next;
	}
	close_pipes(data, NULL);
	status = 0;
	while (i--)
		wait(&status);
	return (status);
}
