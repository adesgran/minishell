/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:05:53 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/02 13:57:11 by adesgran         ###   ########.fr       */
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
	lstclear_token(&data->token);
	free_env(data->env);
	lstclear_cmd(&(data->cmd));
	free(data->last_cmd_status);
	free(data);
	close(0);
	close(1);
	close(2);
}

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	data->cmd = NULL;
	data->env = init_env(env);
	if (!get_env_var(data->env, "SHLVL"))
		push_back_env(data->env, ft_strdup("SHLVL"), ft_strdup("1"));
	data->token = NULL;
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
	return (data);
}
