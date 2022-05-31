/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path_relative.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:35:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/31 13:25:49 by adesgran         ###   ########.fr       */
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
	if (access(str, R_OK))
		return (printf("minishell: %s: No such file or directory\n", str), 1);
	if (access(str, X_OK))
		return (printf("minishell: %s: Permission denied\n", str), 1);
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
