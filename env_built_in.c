/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:52:57 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/25 14:24:05 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_env_built_in(t_cmd *cmd)
{
	if (!cmd || cmd->next)
		return (0);
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->cmd[0], "export"))
		return (1);
	return (0);
}

void	env_built_in(t_data *data, t_cmd *cmd)
{
	int	res;

	res = 0;
	if (!data || !cmd)
		return ;
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		res = mini_cd(data, cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		res = mini_unset(data, cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		res = mini_export(data, cmd->cmd);
	data->last_res = res;
}
