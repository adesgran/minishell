/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:06:26 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/02 11:58:38 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
static char	*get_home(t_data *data, char *str)
{
	t_env	*home;

	home = get_var_env(data->env, "HOME");
	if (!home)
		return (printf("minishell: cd: HOME not set\n"), NULL);
	if (!str)
		return (ft_strdup(home->value));
	return (ft_strjoin(home->value, str));
}

int	mini_cd(t_data *data, char **cmd)
{
	char	*tmp;
	int		res;

	if (cmd[0] && cmd[1] && cmd[2])
		return (printf("minishell: cd: too many arguments"), 1);
	if (!cmd[1])
		tmp = get_home(data, NULL);
	else if (cmd[1][0] == '~')
		tmp = get_home(data, cmd[1] + 1);
	else
		tmp = ft_strdup(cmd[1]);
	if (!tmp)
		return (1);
	res = chdir(tmp);
	if (res)
		return (printf("Can't access %s\n", tmp), free(tmp), 1);
	free(tmp);
	free(get_var_env(data->env, "OLDPWD")->value);
	tmp = get_var_env(data->env, "PWD")->value;
	get_var_env(data->env, "OLDPWD")->value = tmp;
	get_var_env(data->env, "PWD")->value = malloc(sizeof(char) * 1000);
	getcwd(get_var_env(data->env, "PWD")->value, 1000);
	return (0);
}
