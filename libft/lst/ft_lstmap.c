/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:24:32 by adesgran          #+#    #+#             */
/*   Updated: 2021/12/24 12:04:07 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*temp;

	res = malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	temp = res;
	(void) del;
	while (lst)
	{
		temp->next = NULL;
		temp->content = f(lst->content);
		if (lst->next)
			temp->next = malloc(sizeof(t_list));
		lst = lst->next;
		temp = temp->next;
	}
	return (res);
}
