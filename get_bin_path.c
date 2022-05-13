/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:31:31 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 16:48:42 by adesgran         ###   ########.fr       */
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
	printf("ICI 1\n");
	if (!cmd->cmd[0])
		return ;
	printf("ICI 2\n");
	paths = get_path(data);
	printf("ICI 3\n");
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
	printf("ICI 4\n");
	free_paths(paths);
}
