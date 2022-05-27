/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:52:57 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/27 15:20:59 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_exit(t_data *data, char **cmd, int infork)
{
	if (!infork)
	{
		printf("exit\n");
		printf("\x1B[31mGood Bye !\x1B[0m\n");
	}
	free_data(data);
	if (cmd[1])
		exit(ft_atoi(cmd[1]));
	exit(0);
}