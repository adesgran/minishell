/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:29:18 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/06 14:03:34 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*lstnew_token(char *token, int type)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	res->token = token;
	res->expanded = 0;
	res->unexpanded = NULL;
	res->type = type;
	res->next = NULL;
	return (res);
}

t_token	*lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next)
		return (lstlast_token(lst->next));
	else
		return (lst);
}

void	lstadd_back_token(t_token **alst, t_token *new)
{
	t_token	*end;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	end = lstlast_token(alst[0]);
	end->next = new;
}

void	lstdelone_token(t_token *lst)
{
	if (!lst)
		return ;
	free(lst->token);
	free(lst->unexpanded);
	free(lst);
}

void	lstclear_token(t_token **lst)
{
	if (!lst)
		return ;
	if (!*lst)
		return ;
	if (lst[0]->next)
		lstclear_token(&lst[0]->next);
	lstdelone_token(lst[0]);
	lst[0] = NULL;
}
