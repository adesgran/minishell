/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:52:57 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/01 18:02:47 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cmd_size(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static int	check_input(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	mini_exit(t_data *data, char **cmd, int infork)
{
	int	res;

	res = 0;
	if (!infork)
	{
		printf("exit\n");
		if (cmd_size(cmd) > 2)
			return (printf("bash: exit: too many arguments\n"), 1);
		if (check_input(cmd[1]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			res = 2;
		}
		printf("\x1B[31mGood Bye!\x1B[0m\n");
	}
	if (cmd[1] && check_input(cmd[1]))
		res = ft_atoi(cmd[1]);
	else if (cmd[1] && !check_input(cmd[1]))
		res = 2;
	free_data(data);
	exit(res);
}
