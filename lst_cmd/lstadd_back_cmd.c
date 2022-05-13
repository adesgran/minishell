/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:28:53 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/13 10:28:53 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
