/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstlast_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:34:47 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/13 10:34:47 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next)
		return (lstlast_cmd(lst->next));
	else
		return (lst);
}
