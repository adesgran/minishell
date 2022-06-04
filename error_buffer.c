/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:29:06 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/04 18:49:35 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_msg(char *file_name, int type, t_token *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	if (token->expanded && !ft_strlen(file_name))
		ft_putstr_fd(": ambiguous redirect\n", 2);
	else if (type == 1 || (type == 2 && !ft_strlen(file_name)))
		ft_putstr_fd(": No such file or directory !!\n", 2);
	else
		ft_putstr_fd(": Persmission denied\n", 2);
}
