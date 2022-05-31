/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:31:31 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/31 14:42:50 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	error_path(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

char	**get_path(t_data *data)
{
	char	**res;
	char	*path;
	t_env	*env;

	
	env = get_var_env(data->env, "PATH");
	path = NULL;
	if (env)
		path = env->value;
	if (!path)
	{
		res = malloc(sizeof(*res));
		if (res == NULL)
			return (NULL);
		*res = NULL;
		return (res);
	}
	res = ft_split(path, ':');
	return (res);
}

static int	is_builtin(t_cmd *cmd)
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

static int	is_inpath(t_cmd *cmd, char **paths)
{
	int		i;

	i = 0;
	if (!cmd->cmd[0][0])
		return (0);
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
	if (!paths)
		return (1);
	while (cmd)
	{
		if (cmd->cmd && cmd->fd_infile != -1 && cmd->fd_outfile != -1)
		{
			if (is_builtin(cmd) || is_relative_path(cmd))
			{
				if (is_relative_path(cmd))
					cmd->bin_path = get_relative_path(cmd);
				else if (is_builtin(cmd))
					cmd->bin_path = ft_strdup("built_in/");
				if (!cmd->bin_path)
					return (ft_free_tabstr(paths), -1);
			}
			else if (is_inpath(cmd, paths) == -1)
				return (ft_free_tabstr(paths), -1);
			if (!cmd->bin_path)
				error_path(cmd->cmd[0]);
		}
		cmd = cmd->next;
	}
	return (ft_free_tabstr(paths), 0);
}
