/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:23:24 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/11 18:23:24 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lstclear_token(t_token **lst)
{
	t_token	*temp;

	if (lst[0]->next)
		lstclear_token(&lst[0]->next);
	free(lst[0]->token);
	temp = lst[0];
	lst[0] = NULL;
	free(temp);
}
