/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:25:51 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:03:14 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst[0]->next)
		ft_lstclear(&lst[0]->next, del);
	del(lst[0]->content);
	temp = lst[0];
	lst[0] = NULL;
	free(temp);
}
