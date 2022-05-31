/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:03:49 by adesgran          #+#    #+#             */
/*   Updated: 2022/01/21 14:19:20 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	**ft_strs_to_tab(char ***strs)
{
	int	n_line;
	int	l;
	int	**tab;

	if (!strs)
		return (NULL);
	n_line = 0;
	while (strs[n_line])
		n_line++;
	tab = malloc(sizeof(int *) * n_line);
	if (!tab)
		return (NULL);
	l = -1;
	while (strs[++l])
	{
		tab[l] = ft_str_to_tab(strs[l]);
		if (!tab[l])
		{
			while (l--)
				free(tab[l]);
			free(tab);
			return (tab);
		}
	}
	return (tab);
}
