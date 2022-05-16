/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:28:23 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/13 10:28:23 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*lstnew_cmd(void)
{
	t_cmd	*res;

	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->cmd = NULL;
	res->bin_path = NULL;
	res->fd_infile = -2;
	res->fd_outfile = -2;
	res->is_heredoc = 0;
	res->next = NULL;
	return (res);
}
