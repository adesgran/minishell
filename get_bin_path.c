/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:31:31 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 18:23:05 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**get_path(t_data *data)
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

void	get_bin_path(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**paths;

	i = 0;
	if (!cmd->cmd[0])
		return ;
	paths = get_path(data);
	if (!paths)
		return ;
	while (cmd)
	{
		while (paths[i])
		{
			cmd->bin_path = ft_strjoinx(3, paths[i], "/", cmd->cmd[0]);
			if (!cmd->bin_path)
				return (free_paths(paths));
			if (access(cmd->bin_path, X_OK) == 0)
				break ;
			free(cmd->bin_path);
			cmd->bin_path = NULL;
			i++;
		}
		cmd = cmd->next;
	}
	free_paths(paths);
}
