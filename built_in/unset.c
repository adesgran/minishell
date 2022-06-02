/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:10:56 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/02 17:25:37 by adesgran         ###   ########.fr       */
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
			printf("minishell: unset: `%s\': not a valid identifier\n", *strs);
		else if (ft_strcmp(*strs, "_"))
			data->env = remove_var_env(data->env, *strs);
		strs++;
	}
	return (0);
}
