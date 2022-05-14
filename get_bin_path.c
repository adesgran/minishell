/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:31:31 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/14 16:54:05 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_path(t_data *data)
{
	char	**res;
	char	*path;

	path = get_var_env(data->env, "PATH")->value;
	if (!path)
		return (NULL);
	res = ft_split(path, ':');
	return (res);
}

static void	free_paths(char **paths)
{
	char	**init;

	init = paths;
	while (*paths)
	{
		free(*paths);
		paths++;
	}
	free(init);
}

// static int	check_mini_cmd(t_cmd *cmd)
// {
// 	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0
// 			|| ft_strncmp(cmd->cmd[0], "env", 4) == 0
// 			|| ft_strncmp(cmd->cmd[0], "pwd", 4) == 0
// 			|| ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
// 		return (1);
// 	else
// 		return (0);
// }

void	get_bin_path(t_cmd *cmd, char **paths)
{
	int		i;

	i = -1;
	if (!cmd->cmd[0] || !paths)
		return ;
	while (cmd)
	{
		while (paths[++i])
		{
			cmd->bin_path = ft_strjoinx(3, paths[i], "/", cmd->cmd[0]);
			if (!cmd->bin_path)
				return (free_paths(paths));
			if (access(cmd->bin_path, X_OK) == 0)
				break ;
			free(cmd->bin_path);
			cmd->bin_path = NULL;
		}
		cmd = cmd->next;
	}
	free_paths(paths);
}
