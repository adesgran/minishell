/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <adesgran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:05:38 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:02:52 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*end;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	end = ft_lstlast(alst[0]);
	end->next = new;
}
