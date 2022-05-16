/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:31:31 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/16 14:20:23 by mchassig         ###   ########.fr       */
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

int	get_bin_path(t_cmd *cmd, char **paths)
{
	int		i;

	if (!cmd->cmd || !cmd->cmd[0] || !paths)
		return (1);
	while (cmd)
	{
		i = 0;
		while (paths[i] && cmd->fd_infile != -1 && cmd->fd_outfile != -1)
		{
			cmd->bin_path = ft_strjoinx(3, paths[i++], "/", cmd->cmd[0]);
			if (!cmd->bin_path)
				return (free_paths(paths), 1);
			if (access(cmd->bin_path, X_OK) == 0)
				break ;
			free(cmd->bin_path);
			cmd->bin_path = NULL;
		}
		if (!paths[i] && cmd->fd_infile != -1 && cmd->fd_outfile != -1)
		{
			ft_putstr_fd(cmd->cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		cmd = cmd->next;
	}
	return (free_paths(paths), 0);
}
