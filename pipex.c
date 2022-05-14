/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:29:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/14 18:45:46 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	close_pipes(t_data	*data, t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;
	
	temp = data->cmd;
	while (temp)
	{
		i = 0;
		if (temp != cmd)
		{
			if (temp->fd_infile > 2)
				close(temp->fd_infile);
			while (i < temp->nb_outfile)
			{
				if (temp->fd_outfile[i] > 2)
					close(temp->fd_outfile[i]);
				i++;
			}
		}
		temp = temp->next;
	}
}

// static void	close_pipes(t_cmd *cmd)
// {
// 	int	i;
	
// 	while (cmd)
// 	{
// 		if (cmd->fd_infile > 2)
// 			close(cmd->fd_infile);
// 		i = 0;
// 		while (i < cmd->nb_outfile)
// 		{
// 			if (cmd->fd_outfile[i] > 2)
// 				close(cmd->fd_outfile[i]);
// 			i++;
// 		}
// 		cmd = cmd->next;
// 	}
// }

void	call_mini_cmd(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_outfile)
	{
		if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		{
			mini_echo(cmd->cmd, cmd->fd_outfile[i]);
		}
		else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
			mini_env(data, cmd->fd_outfile[i]);
		else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
			mini_pwd(data, cmd->fd_outfile[i]);
		else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
			mini_unset(data, cmd->cmd);
		i++;
	}
}


static int	exec_cmd(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		i;
	
	pid = fork();
	if (pid == -1)
		return (perror("Fork"), 1);
	i = 0;
	if (!pid)
	{
		while (i < cmd->nb_outfile)
		{
			close_pipes(data, cmd);
			dup2(cmd->fd_infile, STDIN_FILENO);
			if (cmd->fd_infile > 2)
				close(cmd->fd_infile);
			dup2(cmd->fd_outfile[i], STDOUT_FILENO);
			if (cmd->fd_outfile[i] > 2)
				close(cmd->fd_outfile[i]);
			if (ft_strncmp(cmd->bin_path, "built_in/", 9) == 0)
				call_mini_cmd(data, cmd);
			else
				execve(cmd->bin_path, cmd->cmd, data->envp);
			i++;
		}
	}
	return (pid);
}

int	add_outfile(t_cmd *cmd, int new_fd)
{
	int	*new_tab;
	int	i;
	
	cmd->nb_outfile++;
	new_tab = malloc(sizeof(int) * cmd->nb_outfile);
	if (!new_tab)
		return (1);
	i = -1;
	while (++i < cmd->nb_outfile - 1)
		new_tab[i] = cmd->fd_outfile[i];
	new_tab[i] = new_fd;
	free(cmd->fd_outfile);
	cmd->fd_outfile = new_tab;
	return (0);
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
			if (add_outfile(cmd, pipefd[0]))
				return (close_pipes(data, NULL), 1);
		}
		else
			if (add_outfile(cmd, 1))
				return (close_pipes(data, NULL), 1);
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
		return (-1); //free des trucs ?
	while (cmd)
	{
		i++;
		exec_cmd(data, cmd);
		cmd = cmd->next;
	}
	status = 0;
	i++;
	close_pipes(data, NULL);
	while (--i)
		wait(&status);
	return (status);
}
