/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:35:16 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/13 10:35:16 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lstclear_cmd(t_cmd **lst)
{
	//t_cmd	*temp;
	// int		i;

	if (!lst)
		return ;
	if (!*lst)
		return ;
	if (lst[0]->next)
		lstclear_cmd(&lst[0]->next);
	lstdelone_cmd(*lst);
	// i = 0;
	// while (lst[0]->cmd && lst[0]->cmd[i])
	// 	free(lst[0]->cmd[i++]);
	// free(lst[0]->cmd);
	// free(lst[0]->bin_path);
	// if (lst[0]->fd_infile > 2)
	// 	close(lst[0]->fd_infile);
	// i = 0;
	// while (i < lst[0]->nb_outfile)
	// {
	// 	if (lst[0]->fd_outfile[i] > 2)
	// 		close(lst[0]->fd_outfile[i]);
	// }
	//temp = lst[0];
	lst[0] = NULL;
	//free(temp);
}
