/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:29:06 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/07 18:27:41 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syntax_error(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (c)
		ft_putchar_fd(c, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

void	redirection_error(char *file_name, int type, t_token *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	if (token->expanded && !ft_strlen(file_name))
		ft_putstr_fd(": ambiguous redirect\n", 2);
	else if (type == 1 || (type == 2 && !ft_strlen(file_name)))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Persmission denied\n", 2);
}
