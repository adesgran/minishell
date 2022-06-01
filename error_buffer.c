/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:29:06 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/01 17:50:24 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*error_buffer(char *old_msg, char *file_name, int type, t_token *token)
{
	char	*new_msg;
	char	*type_msg;

	if (token->expanded && !ft_strlen(file_name))
	{
		file_name = token->unexpanded;
		type_msg = ": ambiguous redirect\n";
	}
	else if (type == 1 || (type == 2 && !ft_strlen(file_name)))
		type_msg = ": No such file or directory\n";
	else
		type_msg = ": Persmission denied\n";
	if (!old_msg)
		new_msg = ft_strjoinx(3, "minishell: ", file_name, type_msg);
	else
		new_msg = ft_strjoinx(4, old_msg, "minishell: ", file_name, type_msg);
	return (free(old_msg), new_msg);
}
