/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:11:39 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/12 14:13:34 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env(int ac, char **av, char **envp)
{
	if (!envp || !*envp)
		return (1);
	while (ft_strncmp(*envp, "_=", 2) == 0)
	{
		printf("%s\n", *envp);
		envp++;
	}
	printf("%s\n", *envp);
	return (0);
}
