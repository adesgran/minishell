/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:57:48 by mchassig          #+#    #+#             */
/*   Updated: 2022/06/04 18:58:57 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_garbage	g_gbg;

void	free_tab_token(void)
{
	int	i;

	i = 0;
	while (g_gbg.tab_token[i])
	{
		lstclear_token(&g_gbg.tab_token[i]);
		i++;
	}
	free(g_gbg.tab_token);
}

void	free_garbage(void)
{
	free_data(g_gbg.data);
	ft_free_tabstr(g_gbg.line_tab);
	free_tab_token();
	free(g_gbg.heredoc_name);
	close(g_gbg.fd_heredoc);
}
