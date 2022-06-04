/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path_relative.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:35:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/04 17:41:53 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_relative_path(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[0][i])
	{
		if (cmd->cmd[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	check_file(char *str)
{
	struct stat	buffer;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (stat(str, &buffer))
		return (ft_putstr_fd(": No such file or directory\n", 2), 1);
	else if (access(str, X_OK))
		return (ft_putstr_fd(": Permission denied\n", 2), 1);
	return (0);
}

char	*get_relative_path(t_cmd *cmd)
{
	char	*res;

	res = ft_strdup(cmd->cmd[0]);
	if (check_file(res))
		return (free(res), NULL);
	return (res);
}
