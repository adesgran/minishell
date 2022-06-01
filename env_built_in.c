/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:52:57 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/01 15:11:06 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_env_built_in(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd || cmd->next)
		return (0);
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->cmd[0], "export") && cmd->cmd[1])
		return (1);
	if (!ft_strcmp(cmd->cmd[0], "exit"))
		return (1);
	return (0);
}

int	env_built_in(t_data *data, t_cmd *cmd)
{
	int	res;

	res = 0;
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		res = mini_cd(data, cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		res = mini_unset(data, cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export") && cmd->cmd[1])
		res = mini_export(data, cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		res = mini_exit(data, cmd->cmd, 0);
	return (res);
}

void	call_built_in_fork(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
	{
		mini_echo(cmd->cmd);
	}
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		mini_env(data);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		mini_pwd(data);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		mini_unset(data, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		mini_export(data, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		mini_cd(data, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		mini_exit(data, cmd->cmd, 1);
}
