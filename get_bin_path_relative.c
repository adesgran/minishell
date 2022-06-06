/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path_relative.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:35:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/06 13:58:07 by mchassig         ###   ########.fr       */
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

static void	check_file(char *str)
{
	struct stat	buffer;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (stat(str, &buffer))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Permission denied\n", 2);
}

char	*get_relative_path(t_cmd *cmd)
{
	char	*res;

	res = ft_strdup(cmd->cmd[0]);
	if (access(res, X_OK))
		return (check_file(res), free(res), NULL);
	return (res);
}
