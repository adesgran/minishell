/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:52:57 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/04 17:51:36 by adesgran         ###   ########.fr       */
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

static int	check_max(char *str)
{
	char	*max;
	int		i;

	while (*str == '0')
		str++;
	if (!*str)
		return (0);
	if (ft_strlen(str) > 19)
		return (0);
	if (ft_strlen(str) < 19)
		return (1);
	max = ft_strdup("9223372036854775807");
	if (!max)
		return (1);
	i = 0;
	while (max[i])
	{
		if (str[i] > max[i])
			return (free(max), 0);
		if (str[i] < max[i])
			return (free(max), 1);
		i++;
	}
	return (free(max), 1);
}

static int	check_input(char *str)
{
	char	*str_init;

	str_init = str;
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (check_max(str_init));
}

int	mini_exit(t_data *data, char **cmd, int infork)
{
	int	res;

	res = 0;
	if (!infork)
	{
		printf("exit\n");
		if (cmd_size(cmd) > 2)
			return (ft_putstr_fd("bash: exit: too many arguments\n", 2), 1);
		if (check_input(cmd[1]) == 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			res = 2;
		}
	}
	if (cmd[1] && check_input(cmd[1]))
		res = ft_atoi(cmd[1]);
	else if (cmd[1] && !check_input(cmd[1]))
		res = 2;
	else if (!cmd[1])
		res = ft_atoi(data->last_cmd_status);
	free_data(data);
	exit(res);
}
