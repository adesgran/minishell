/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:31:31 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/17 17:18:46 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_path(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

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

// static void	free_paths(char **paths)
// {
// 	char	**init;

// 	init = paths;
// 	while (*paths)
// 	{
// 		free(*paths);
// 		paths++;
// 	}
// 	free(init);
// }

int	is_builtin(t_cmd *cmd)
{
	if (cmd->fd_infile != -1 && cmd->fd_outfile != -1
		&& (ft_strcmp(cmd->cmd[0], "echo") == 0
		|| ft_strcmp(cmd->cmd[0], "env") == 0
		|| ft_strcmp(cmd->cmd[0], "export") == 0
		|| ft_strcmp(cmd->cmd[0], "pwd") == 0
		|| ft_strcmp(cmd->cmd[0], "unset") == 0
		|| ft_strcmp(cmd->cmd[0], "cd") == 0))
	{
		return (1);
	}
	return (0);
}

int	is_inpath(t_cmd *cmd, char **paths)
{
	int		i;

	i = 0;
	while (paths[i] && cmd->fd_infile != -1 && cmd->fd_outfile != -1)
	{
		cmd->bin_path = ft_strjoinx(3, paths[i++], "/", cmd->cmd[0]);
		if (!cmd->bin_path)
			return (-1);
		if (access(cmd->bin_path, X_OK) == 0)
			return (1);
		free(cmd->bin_path);
		cmd->bin_path = NULL;
	}
	return (0);
}

int	get_bin_path(t_cmd *cmd, char **paths)
{
	if (!cmd->cmd || !cmd->cmd[0] || !paths)
		return (1);
	while (cmd)
	{
		if (cmd->fd_infile != -1 && cmd->fd_outfile != -1)
		{
			if (is_builtin(cmd))
				cmd->bin_path = "built_in/";
			else if (is_inpath(cmd, paths) == -1)
				return (ft_free_tabstr(paths), -1);
			if (!cmd->bin_path)
				error_path(cmd->cmd[0]);
		}
		cmd = cmd->next;
	}
	return (ft_free_tabstr(paths), 0);
}
