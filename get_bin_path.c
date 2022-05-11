/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:31:31 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/11 17:54:47 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**get_path(void)
{
	char	**res;
	char	*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	res = ft_split(path, ':');
	free(path);
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

void	get_bin_path(t_cmd *cmd)
{
	int		i;
	char	**paths;

	i = 0;
	if (!cmd->cmd[0])
		return ;
	paths = get_path();
	if (!paths)
		return ;
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
	free_paths(paths);
}
