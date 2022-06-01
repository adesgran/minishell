/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:55:00 by adesgran          #+#    #+#             */
/*   Updated: 2022/06/01 16:42:52 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_garbage	gbg;

void	get_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	get_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		free_garbage(1);
		printf("\n");
		exit(1);
	}
}
