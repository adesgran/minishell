/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:56:34 by mchassig          #+#    #+#             */
/*   Updated: 2022/03/01 17:28:09 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_freecmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i].fd_write != -2)
	{
		ft_free_split(cmd[i].cmd);
		cmd[i].cmd = NULL;
		free(cmd[i].bin);
		cmd[i].bin = NULL;
		close(cmd[i].fd_read);
		cmd[i].fd_read = -1;
		close(cmd[i].fd_write);
		cmd[i].fd_write = -1;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

t_cmd	*ft_setcmd(char *infile, int argc)
{
	t_cmd	*new;
	int		i;
	int		size;

	if (ft_strncmp(infile, "here_doc", 8) == 0 && argc > 5)
		size = argc - 4;
	else
		size = argc - 3;
	new = malloc(sizeof(t_cmd) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i].cmd = NULL;
		new[i].bin = NULL;
		new[i].fd_read = -1;
		new[i].fd_write = -1;
		i++;
	}
	new[i].cmd = NULL;
	new[i].bin = NULL;
	new[i].fd_read = -2;
	new[i].fd_write = -2;
	return (new);
}
