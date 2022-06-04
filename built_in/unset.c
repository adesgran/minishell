/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:10:56 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/04 17:54:01 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_identifier(char *str)
{
	if (!ft_isalpha(*str))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	mini_unset(t_data *data, char **strs)
{
	if (!strs)
		return (0);
	strs++;
	while (*strs)
	{
		if (!check_identifier(*strs))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(*strs, 2);
			ft_putendl_fd("\': not a valid identifier", 2);
		}
		else if (ft_strcmp(*strs, "_"))
			data->env = remove_var_env(data->env, *strs);
		strs++;
	}
	return (0);
}
