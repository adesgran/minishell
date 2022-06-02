/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:32:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/02 15:42:53 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_pwd(t_data *data)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 1001);
	if (!pwd)
		return (1);
	if (!getcwd(pwd, 1000))
		return (free(pwd), 2);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(pwd);
	(void)data;
	return (0);
}
