/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tabstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:41:37 by adesgran          #+#    #+#             */
/*   Updated: 2022/05/16 15:45:06 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_free_tabstr(char **tab)
{
	char	**init;

	if (!tab)
		return ;
	init = tab;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(init);
}
