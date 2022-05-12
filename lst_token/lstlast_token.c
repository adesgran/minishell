/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstlast_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:08:52 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/11 18:08:52 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next)
		return (lstlast_token(lst->next));
	else
		return (lst);
}
