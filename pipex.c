/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:29:34 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/01 14:53:51 by mchassig         ###   ########.fr       */
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
			else
				close(pipefd[0]);
			if (cmd->fd_outfile == -2)
				cmd->fd_outfile = pipefd[1];
			else
				close(pipefd[1]);
		}
		else
			if (cmd->fd_outfile == -2)
				cmd->fd_outfile = 1;
		cmd = cmd->next;
	}
	return (0);
}

static pid_t	exec_cmd(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
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
			call_built_in_fork(data, cmd);
		else
		{
			increment_shlvl(data);
			execve(cmd->bin_path, cmd->cmd, env_to_tab(data->env));
		}
		return (close(cmd->fd_outfile), close(cmd->fd_infile), free_data(data),
			exit(EXIT_SUCCESS), 0);
	}
	if (pid != -1 && cmd->is_heredoc)
		unlink(cmd->heredoc);
	return (pid);
}

int	wait_child(pid_t pid, int i, int ret)
{
	int	status;

	status = 0;
	while (i-- > 1)
		wait(&status);
	if (i == 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	return (ret);
}

int	pipex(t_data *data, t_cmd *cmd)
{
	int		i;
	pid_t	pid;
	int		ret;

	if (set_pipefd(cmd, data))
		return (-1);
	i = 0;
	ret = 0;
	while (cmd)
	{
		if (cmd->fd_infile != -1 && cmd->fd_outfile != -1 && cmd->bin_path)
		{
			pid = exec_cmd(data, cmd) == -1;
			if (pid == -1)
				break ;
			i++;
			ret = 0;
		}
		else if (cmd->fd_infile == -1 || cmd->fd_outfile == -1)
			ret = 1;
		else if (!cmd->bin_path)
			ret = 127;
		cmd = cmd->next;
	}
	return (close_pipes(data, NULL), wait_child(pid, i, ret));
}
