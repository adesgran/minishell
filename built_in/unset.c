/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:10:56 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/02 15:46:33 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_unset(t_data *data, char **strs)
{
	if (!strs)
		return (0);
	strs++;
	while (*strs)
	{
		if (ft_strcmp(*strs, "_"))
			data->env = remove_var_env(data->env, *strs);
		strs++;
	}
	return (0);
}
