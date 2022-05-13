/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:10:56 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/13 14:46:05 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_unset(t_data *data, char **strs)
{
	if (!strs)
		return (0);
	while (*strs)
	{
		data->env = remove_var_env(data->env, *strs);
		strs++;
	}
	return (0);
}
