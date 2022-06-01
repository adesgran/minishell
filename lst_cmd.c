/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:59:15 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/01 15:04:23 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*lstnew_cmd(int i)
{
	t_cmd	*res;
	char	*num_cmd;

	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->cmd = NULL;
	res->bin_path = NULL;
	res->fd_infile = -2;
	res->fd_outfile = -2;
	res->is_heredoc = 0;
	num_cmd = ft_itoa(i);
	if (!num_cmd)
		return (free(res), NULL);
	res->heredoc = ft_strjoin("heredoc", num_cmd);
	free(num_cmd);
	if (!res->heredoc)
		return (free(res), NULL);
	res->next = NULL;
	return (res);
}

t_cmd	*lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next)
		return (lstlast_cmd(lst->next));
	else
		return (lst);
}

void	lstadd_back_cmd(t_cmd **alst, t_cmd *new)
{
	t_cmd	*end;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	end = lstlast_cmd(alst[0]);
	end->next = new;
}

void	lstdelone_cmd(t_cmd *lst)
{
	ft_free_tabstr(lst->cmd);
	free(lst->bin_path);
	if (lst->fd_infile > 2)
		close(lst->fd_infile);
	if (lst->is_heredoc > 0)
		unlink(lst->heredoc);
	else if (lst->fd_outfile > 2)
		close(lst->fd_outfile);
	free(lst->heredoc);
	free(lst);
}

void	lstclear_cmd(t_cmd **lst)
{
	if (!lst)
		return ;
	if (!*lst)
		return ;
	if (lst[0]->next)
		lstclear_cmd(&lst[0]->next);
	lstdelone_cmd(*lst);
	*lst = NULL;
}
