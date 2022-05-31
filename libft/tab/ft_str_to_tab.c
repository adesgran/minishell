/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 12:53:34 by adesgran          #+#    #+#             */
/*   Updated: 2022/01/09 13:15:01 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	*ft_str_to_tab(char **s)
{
	int	len;
	int	i;
	int	*tab;

	if (!s)
		return (NULL);
	if (!*s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	tab = malloc(sizeof(int) * len);
	if (!tab)
		return (tab);
	i = 0;
	while (i < len)
	{
		tab[i] = ft_atoi(s[i]);
		i++;
	}
	return (tab);
}
