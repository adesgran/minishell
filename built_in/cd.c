/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:06:26 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/25 13:06:06 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_list(char **list)
{
	char	**init;

	init = list;
	while (*list)
	{
		free(*list);
		list++;
	}
	free(init);
}

static int	open_check(char **dir, char *new)
{
	char *res;
	DIR	*dirflux;

	res = ft_strjoinx(3, *dir, "/", new);
	dirflux = opendir(res);
	if (!dirflux)
	{
		printf("minishell : cd :Can't access %s folder\n", res);
		return (free(res), 1);
	}
	closedir(dirflux);
	free(*dir);
	*dir = res;
	return (0);
}

static char	*check_dirs(t_data *data, char *str)
{
	int	i;
	char	*dir;
	char	**dir_list;

	if (*str == '/')
		dir = ft_strdup("");
	else
		dir = ft_strdup(get_var_env(data->env, "PWD")->value);
	i = 0;
	dir_list = ft_split(str, '/');
	while (dir_list[i])
	{
		if (open_check(&dir, dir_list[i]))
			return (free(dir), free_list(dir_list), NULL);
		i++;
	}
	free_list(dir_list);
	return (dir);
}

int	mini_cd(t_data *data, char **cmd)
{
	char	*old_dir;
	char	*new_dir;

	if (*cmd && cmd[1])
		return (printf("minishell: cd: too many arguments"), 1);
	new_dir = check_dirs(data, *cmd);
	if (!new_dir)
		return (1);
	old_dir = get_var_env(data->env, "PWD")->value;
	free(get_var_env(data->env, "OLD_PWD")->value);
	get_var_env(data->env, "OLD_PWD")->value = old_dir;
	get_var_env(data->env, "PWD")->value = new_dir;
	return (0);
}
