/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdelone_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:35:06 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/13 10:35:06 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lstdelone_cmd(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst->cmd[i])
		free(lst->cmd[i++]);
	free(lst->cmd);
	free(lst->bin_path);
	if (lst->fd_infile > 2)
		close(lst->fd_infile);
	i = 0;
	while (i < lst->nb_outfile)
	{
		if (lst->fd_outfile[i] > 2)
			close(lst->fd_outfile[i]);
		i++;
	}
	free(lst);
}
