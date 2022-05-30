/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:05:53 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/30 13:10:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	increment_shlvl(t_data *data)
{
	t_env	*shlvl;
	char	*tmp;

	shlvl = get_var_env(data->env, "SHLVL");
	tmp = shlvl->value;
	shlvl->value = ft_itoa(ft_atoi(tmp) + 1);
	if (shlvl->value)
		free(tmp);
	else
		shlvl->value = tmp;
}

void	free_data(t_data *data)
{
	free_env(data->env);
	lstclear_cmd(&(data->cmd));
	free(data->last_cmd_status);
	free(data);
}

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->cmd = NULL;
	data->env = init_env(env);
	if (!data->env)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	data->envp = env;
	data->n_cmd = 0;
	data->last_cmd_status = ft_itoa(0);
	if (!data->last_cmd_status)
		return (free_env(data->env), free(data), NULL);
	increment_shlvl(data);
	return (data);
}
