/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:52:57 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/30 16:58:53 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_exit(t_data *data, char **cmd, int infork)
{
	int	res;

	if (!infork)
	{
		printf("exit\n");
		printf("\x1B[31mGood Bye!\x1B[0m\n");
	}
	res = 0;
	if (cmd[1])
		res = ft_atoi(cmd[1]);
	free_data(data);
	exit(res);
}
