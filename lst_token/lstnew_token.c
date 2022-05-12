/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:57:42 by mchassig          #+#    #+#             */
/*   Updated: 2022/05/11 17:57:42 by mchassig         ###   ########.fr       */
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
	res->type = type;
	res->next = NULL;
	return (res);
}
